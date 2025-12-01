package main

import (
	"crypto/rsa"
	"flag"
	"fmt"
	"os"
)

func printCode(generateOTP *string, privateKey *rsa.PrivateKey) {
	encrypted, err := os.ReadFile(*generateOTP)
	if err != nil {
		fmt.Printf("can't open the key: %v\n", err)
		return
	}
	secret, err := decryptKey(privateKey, encrypted)
	if err != nil {
		fmt.Printf("couldn't decrypt the key: %v\n", err)
		return
	}
	step := int64(30)
	digits := 6
	otp, err := GenerateTOTP(string(secret[:]), step, digits)
	if err != nil {
		fmt.Println(string(secret[:]))
		fmt.Printf("Error generating TOTP: %v\n", err)
		return
	}

	fmt.Printf("Current TOTP code: %s\n", otp)
}

func checkingKeys() (*rsa.PrivateKey, *rsa.PublicKey, error) {
	var privateKey *rsa.PrivateKey
	var publicKey *rsa.PublicKey

	_, err := os.ReadFile("private_key.pem")
	if err != nil {
		var err2 error
		privateKey, publicKey, err2 = key_gen()
		if err2 != nil {
			return nil, nil, fmt.Errorf("error generating keys: %v", err2)
		}
		return privateKey, publicKey, nil
	} else {
		var err2 error
		privateKey, err2 = loadPrivateKey("private_key.pem")
		if err2 != nil {
			return nil, nil, fmt.Errorf("error loading private key: %v", err2)
		}
		return privateKey, &privateKey.PublicKey, nil
	}
}

func creatingKey(generateKey *string, publicKey *rsa.PublicKey) {
	fileBytes, err := os.ReadFile(*generateKey)
	if err != nil {
		fmt.Printf("Error reading key file: %v\n", err)
		return
	}
	encripted, err := encryptKey(publicKey, string(fileBytes))
	if err != nil {
		fmt.Printf("couldn't encrypt the key: %v\n", err)
		return
	}
	os.WriteFile("ft_otp.key", encripted, 0o777)
}

func main() {

	generateKey := flag.String("g", "", "Stock an  hexadecimal key of at least 64 characters long to use to generate the TOTPs")
	generateOTP := flag.String("k", "", "Generates a new temporary password based on the key given as argument and prints it on the standard output.")

	KeySet := false
	OtpSet := false
	flag.Parse()
	flag.Visit(func(f *flag.Flag) {
		switch f.Name {
		case "g":
			KeySet = true
		case "k":
			OtpSet = true
		}
	})
	if !KeySet && !OtpSet {
		fmt.Println("To use ft_otp, use \n\t [-g] to generate a key ;\n\t [-k] to generate a OTP")
		return
	}
	privateKey, publicKey, err := checkingKeys()
	if err != nil {
		return
	}
	if KeySet {
		creatingKey(generateKey, publicKey)
	}
	if OtpSet {
		printCode(generateOTP, privateKey)
	}

}
