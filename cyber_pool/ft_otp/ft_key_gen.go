package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"crypto/x509"
	"encoding/base64"
	"encoding/pem"
	"fmt"
	"os"
)

func encryptKey(publicKey *rsa.PublicKey, msg string) ([]byte, error) {

	ciphertext, err := rsa.EncryptOAEP(sha256.New(), rand.Reader, publicKey, []byte(msg), nil)
	if err != nil {
		return nil, fmt.Errorf("encryption error: %v", err)
	}
	return ciphertext, nil
}

func decryptKey(privateKey *rsa.PrivateKey, ciphertext []byte) ([]byte, error) {
	decrypted, err := rsa.DecryptOAEP(sha256.New(), rand.Reader, privateKey, ciphertext, nil)
	if err != nil {
		fmt.Println("Decryption error:", err)
		return nil, fmt.Errorf("decryption error %v", err)
	}
	return decrypted, nil
}

func key_gen() (*rsa.PrivateKey, *rsa.PublicKey, error) {
	// Generate key pair
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return nil, nil, fmt.Errorf("key generation error: %v", err)
	}
	publicKey := &privateKey.PublicKey

	// Save private key to file
	privateKeyFile, err := os.Create("private_key.pem")
	if err != nil {
		return nil, nil, fmt.Errorf("failed to create private key file: %v", err)
	}
	defer privateKeyFile.Close()

	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}
	if err := pem.Encode(privateKeyFile, privateKeyPEM); err != nil {
		return nil, nil, fmt.Errorf("failed to write private key: %v", err)
	}

	// Save public key to file
	publicKeyFile, err := os.Create("public_key.pem")
	if err != nil {
		return nil, nil, fmt.Errorf("failed to create public key file: %v", err)
	}
	defer publicKeyFile.Close()

	publicKeyBytes, err := x509.MarshalPKIXPublicKey(publicKey)
	if err != nil {
		return nil, nil, fmt.Errorf("failed to marshal public key: %v", err)
	}
	publicKeyPEM := &pem.Block{
		Type:  "PUBLIC KEY",
		Bytes: publicKeyBytes,
	}
	if err := pem.Encode(publicKeyFile, publicKeyPEM); err != nil {
		return nil, nil, fmt.Errorf("failed to write public key: %v", err)
	}

	fmt.Println("Keys saved to private_key.pem and public_key.pem")

	// Encrypt
	plaintext := []byte("RSA encryption in Go!")
	ciphertext, err := rsa.EncryptOAEP(sha256.New(), rand.Reader, publicKey, plaintext, nil)
	if err != nil {
		return nil, nil, fmt.Errorf("encryption error: %v", err)
	}
	fmt.Printf("Ciphertext (base64): %s\n", base64.StdEncoding.EncodeToString(ciphertext))

	// Decrypt
	decrypted, err := rsa.DecryptOAEP(sha256.New(), rand.Reader, privateKey, ciphertext, nil)
	if err != nil {
		fmt.Println("Decryption error:", err)
		return nil, nil, fmt.Errorf("decryption error %v", err)
	}
	fmt.Printf("Decrypted: %s\n", decrypted)
	return privateKey, publicKey, nil
}

func loadPrivateKey(filename string) (*rsa.PrivateKey, error) {
	keyData, err := os.ReadFile(filename)
	if err != nil {
		return nil, fmt.Errorf("failed to read private key file: %v", err)
	}

	block, _ := pem.Decode(keyData)
	if block == nil {
		return nil, fmt.Errorf("failed to decode PEM block")
	}

	privateKey, err := x509.ParsePKCS1PrivateKey(block.Bytes)
	if err != nil {
		return nil, fmt.Errorf("failed to parse private key: %v", err)
	}

	return privateKey, nil
}
