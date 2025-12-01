package main

import (
	"crypto/hmac"
	"crypto/sha1"
	"encoding/binary"
	"encoding/hex"
	"fmt"
	"math"
	"time"
)

func GenerateTOTP(secret string, step int64, digits int) (string, error) {
	key, err := hex.DecodeString(secret)
	if err != nil {
		return "", fmt.Errorf("failed to decode secret: %v", err)
	}

	timeStep := time.Now().Unix() / step
	msg := make([]byte, 8)
	binary.BigEndian.PutUint64(msg, uint64(timeStep))

	mac := hmac.New(sha1.New, key)
	mac.Write(msg)
	hash := mac.Sum(nil)

	offset := hash[len(hash)-1] & 0x0F
	code := (int32(hash[offset])&0x7F)<<24 |
		(int32(hash[offset+1])&0xFF)<<16 |
		(int32(hash[offset+2])&0xFF)<<8 |
		(int32(hash[offset+3]) & 0xFF)

	otp := int(code) % int(math.Pow10(digits))
	format := fmt.Sprintf("%%0%dd", digits)
	return fmt.Sprintf(format, otp), nil
}
