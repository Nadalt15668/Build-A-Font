#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Constants.h"

using namespace sf;

class FilesWriter
{
public:
	static void WriteCharacterSVG(std::string characterName, std::vector<RectangleShape>** character) {
		std::vector<RectangleShape> charData = **character;
		// Moves the drawing to the corner
		for (auto& line : charData)
			line.move(-DRAWING_POS.x + DRAWING_DIM.x / 2, -DRAWING_POS.y + DRAWING_DIM.y / 2);
		// Writes the drawing to an svg file in the temporary folder
		CreateCharPNG(characterName, charData);
	};
	static bool CreateSpacePNG()
	{
		RenderTexture tex;
		tex.create(DRAWING_DIM.x, DRAWING_DIM.y);
		tex.clear(Color::Transparent);
		tex.display();
		return tex.getTexture().copyToImage().saveToFile(TEMPORARY_DIR + "/" + "space.png");
	}
	static void WriteConversionBAT(std::vector<std::string> charsNames)
	{
		std::ofstream batfile;
		batfile.open("./" + (std::string)CONV_SCRIPT);
		batfile << "@echo off\n";
		for (auto& filename : charsNames)
		{
			batfile << "convert -alpha remove " << TEMPORARY_DIR_BAT << "\\" << filename << ".png " << TEMPORARY_DIR_BAT << "\\" << filename << ".pnm\n";
			batfile << POTRACE_LOC << " " << TEMPORARY_DIR_BAT << "\\" << filename << ".pnm -s -o " << TEMPORARY_DIR_BAT << "\\" << filename << ".svg\n";
			batfile << "del " << TEMPORARY_DIR_BAT << "\\" << filename << ".png\n";
			batfile << "del " << TEMPORARY_DIR_BAT << "\\" << filename << ".pnm\n";
		}
		batfile << "convert -alpha remove " << TEMPORARY_DIR_BAT << "\\" << "space.png " << TEMPORARY_DIR_BAT << "\\" << "space.pnm\n";
		batfile << POTRACE_LOC << " " << TEMPORARY_DIR_BAT << "\\" << "space.pnm -s -o " << TEMPORARY_DIR_BAT << "\\" << "space.svg\n";
		batfile << "del " << TEMPORARY_DIR_BAT << "\\" << "space.png\n";
		batfile << "del " << TEMPORARY_DIR_BAT << "\\" << "space.pnm\n";
		batfile.close();
	};
	static void WriteJSON(std::string copyright, std::string familyname, std::string version, std::string path)
	{
#define ASCENT 96
#define DESCENT 32
#define EM 256
#define ENCODING "UnicodeFull"
#define LANG "English (US)"
#define STYLE "Regular"
		std::ofstream jsonfile;
		jsonfile.open(TEMPORARY_DIR + "/" + "fontattr.json");
		jsonfile << "{\n\n";
		// -----PROPS-----
		jsonfile << "\t\"props\": {\n";
		jsonfile << "\t\t\"ascent\": " << ASCENT << ",\n";
		jsonfile << "\t\t\"descent\": " << DESCENT << ",\n";
		jsonfile << "\t\t\"em\": " << EM << ",\n";
		jsonfile << "\t\t\"encoding\": \"" << ENCODING << "\",\n";
		jsonfile << "\t\t\"lang\": \"" << LANG << "\",\n";
		jsonfile << "\t\t\"family\": \"" << familyname << "\",\n";
		jsonfile << "\t\t\"style\": \"" << STYLE << "\",\n";
		jsonfile << "\t\t\"familyname\": \"" << familyname << "\",\n";
		jsonfile << "\t\t\"fontname\": \"" << familyname << "-" << STYLE << "\",\n";
		jsonfile << "\t\t\"fullname\": \"" << familyname << " " << STYLE << "\"\n";
		jsonfile << "\t},\n";
		// -----GLYPHS-----
		AddGlyphs(jsonfile);
		jsonfile << "},\n";
		// -----SFNT NAMES-----
		jsonfile << "\t\"sfnt_names\": [\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"Copyright\", \"" << copyright << "\" ],\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"Family\", \"" << familyname << "\" ],\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"SubFamily\", \"" << STYLE << "\" ],\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"UniqueID\", \"" << familyname << version << "\" ],\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"Fullname\", \"" << familyname << " " << STYLE << "\" ],\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"Version\", \"Version " << version << "\" ],\n";
		jsonfile << "\t\t[ \"" << LANG << "\", \"PostScriptName\", \"" << familyname << "-" << version << "\" ]\n";
		jsonfile << "\t\],";
		// -----OTHER-----
		jsonfile << "\t\"input\": \".\",\n";
		jsonfile << "\t\"output\": [\"" << path << "/" << familyname << ".ttf" << "\"],\n";
		jsonfile << "\"# vim: set et sw=2 ts=2 sts=2:\": false\n";
		jsonfile << "}";
		jsonfile.close();
	};

private:
	static bool CreateCharPNG(std::string charName, std::vector<RectangleShape>& charData)
	{
		RenderTexture tex;
		tex.create(DRAWING_DIM.x, DRAWING_DIM.y);
		tex.clear(Color::Transparent);
		for (auto& line : charData)
			tex.draw(line);
		tex.display();
		return tex.getTexture().copyToImage().saveToFile(TEMPORARY_DIR + "/" + charName + ".png");
	};
	// JSON helper methods
	static void AddGlyphs(std::ofstream& jsonfile)
	{
		jsonfile << "\t\"glyphs\": {\n";
		std::string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string symbolsKeys = "&'\"@:,=!/)-%+?(;. ";
		std::map<char, std::pair<std::string, bool>> symbols = {
			{'&',	std::make_pair("ampersand",			false)},
			{'\'',	std::make_pair("apostrophe",		false)},
			{'"',	std::make_pair("double_apostrophe", false)},
			{'@',	std::make_pair("at",				false)},
			{':',	std::make_pair("colon",				false)},
			{',',	std::make_pair("comma",				false)},
			{'=',	std::make_pair("equals",			false)},
			{'!',	std::make_pair("exclamation_mark",	false)},
			{'/',	std::make_pair("forward_slash",		false)},
			{')',	std::make_pair("right_parenthesis",	false)},
			{'-',	std::make_pair("minus",				false)},
			{'%',	std::make_pair("percent",			false)},
			{'+',	std::make_pair("plus",				false)},
			{'?',	std::make_pair("question_mark",		false)},
			{'(',	std::make_pair("left_parenthesis",	false)},
			{';',	std::make_pair("semicolon",			false)},
			{'.',	std::make_pair("dot",				false)},
			{' ',	std::make_pair("space",				true)}
		};
		for (auto& character : characters)
		{
			jsonfile << "\t\t\"0x" << std::hex << (int)character << "\": {\n";
			jsonfile << "\t\t\t\"src\": \"" << character;
			if (isdigit(character))
				jsonfile << ".svg\",\n";
			else if (isalpha(character) && islower(character))
				jsonfile << "_small.svg\",\n";
			else if (isalpha(character) && !islower(character))
				jsonfile << "_capital.svg\",\n";
			jsonfile << "\t\t\t\"width\": " << DRAWING_DIM.x << "},\n";
		}
		for (auto& symbol : symbolsKeys)
		{
			std::pair<std::string, bool> symbolPair = symbols.at(symbol);
			AddSymbol(jsonfile, symbolPair.first, symbol, symbolPair.second);
		}
	}
	static void AddSymbol(std::ofstream& jsonfile, std::string svgname, char symbol, bool isLast)
	{
		jsonfile << "\t\t\"0x" << std::hex << (int)symbol << "\": {\n";
		jsonfile << "\t\t\t\"src\": \"" << svgname << ".svg\",\n";
		jsonfile << "\t\t\t\"width\": " << DRAWING_DIM.x;
		if (isLast)
			jsonfile << "}\n";
		else
			jsonfile << "},\n";
	};
};