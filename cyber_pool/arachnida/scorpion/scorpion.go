/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scorpion.go                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:15:20 by codespace         #+#    #+#             */
/*   Updated: 2025/11/25 21:59:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

package main

import (
	"fmt"
	"log"
	"os"

	"github.com/rwcarlsen/goexif/exif"
	"github.com/tidwall/gjson"
)

var Reset = "\033[0m"
var Red = "\033[31m"
var Green = "\033[32m"
var Yellow = "\033[33m"
var Blue = "\033[34m"
var Magenta = "\033[35m"
var Cyan = "\033[36m"
var Gray = "\033[37m"
var White = "\033[97m"

func main() {
	var err error
	var imgFile *os.File
	var metaData *exif.Exif
	var jsonByte []byte
	var jsonString string

	imgFile, err = os.Open("sample.jpg")
	if err != nil {
		log.Fatal(err.Error())
	}

	metaData, err = exif.Decode(imgFile)
	if err != nil {
		log.Fatal(err.Error())
	}

	jsonByte, err = metaData.MarshalJSON()
	if err != nil {
		log.Fatal(err.Error())
	}

	jsonString = string(jsonByte)

	fmt.Println(Red + "\n ************************************* EXIF DATA ************************************* \n" + Reset)
	fmt.Println(Green + "\n ********************************* CAMERA SETTINGS ********************************* \n" + Reset)

	fmt.Println(Blue + "Model: " + Reset + gjson.Get(jsonString, "Model").String())
	fmt.Println(Blue + "Make: " + Reset + gjson.Get(jsonString, "Make").String())

	fmt.Println(Blue + "Orientation: " + Reset + gjson.Get(jsonString, "Orientation").String())
	fmt.Println(Blue + "ApertureValue: " + Reset + gjson.Get(jsonString, "ApertureValue").String())
	fmt.Println(Blue + "ShutterSpeedValue: " + Reset + gjson.Get(jsonString, "ShutterSpeedValue").String())
	fmt.Println(Blue + "FocalLength: " + Reset + gjson.Get(jsonString, "FocalLength").String())
	fmt.Println(Blue + "MeteringMode: " + Reset + gjson.Get(jsonString, "MeteringMode").String())
	fmt.Println(Blue + "ISOSpeedRatings: " + Reset + gjson.Get(jsonString, "ISOSpeedRatings").String())

	fmt.Println(Green + "\n ********************************** IMAGE METRICS ********************************** \n" + Reset)

	fmt.Println(Blue + "ImageWidth: " + Reset + gjson.Get(jsonString, "ImageWidth").String())
	fmt.Println(Blue + "ImageLength: " + Reset + gjson.Get(jsonString, "ImageLength").String())
	fmt.Println(Blue + "ResolutionUnit: " + Reset + gjson.Get(jsonString, "ResolutionUnit").String())
	fmt.Println(Blue + "ColorSpace: " + Reset + gjson.Get(jsonString, "ColorSpace").String())
	fmt.Println(Blue + "FileSource: " + Reset + gjson.Get(jsonString, "FileSource").String())

	fmt.Println(Green + "\n ********************************** OTHER SETTINGS ********************************* \n" + Reset)

	fmt.Println(Blue + "DateTime: " + Reset + gjson.Get(jsonString, "DateTime").String())
	fmt.Println(Blue + "DateTimeOriginal: " + Reset + gjson.Get(jsonString, "DateTimeOriginal").String())
	fmt.Println(Blue + "SubjectLocation: " + Reset + gjson.Get(jsonString, "SubjectLocation").String())
	fmt.Println(Blue + "ImageDescription: " + Reset + gjson.Get(jsonString, "ImageDescription").String())
	fmt.Println(Blue + "Copyright: " + Reset + gjson.Get(jsonString, "Copyright").String())

	fmt.Println(Blue + "Software: " + Reset + gjson.Get(jsonString, "Software").String())

}
