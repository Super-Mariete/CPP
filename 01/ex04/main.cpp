/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by marta             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

// Replace all occurrences of s1 with s2 in the string
std::string replaceAll(std::string str, const std::string& s1, const std::string& s2)
{
	std::string result;
	size_t pos = 0;
	size_t found;

	if (s1.empty())
		return str;

	while ((found = str.find(s1, pos)) != std::string::npos)
	{
		result += str.substr(pos, found - pos);
		result += s2;
		pos = found + s1.length();
	}
	result += str.substr(pos);

	return result;
}

int main(int argc, char** argv)
{
	// Check arguments
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	// Open input file
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
		return 1;
	}

	// Open output file
	std::string outputFilename = filename + ".replace";
	std::ofstream outputFile(outputFilename.c_str());
	if (!outputFile.is_open())
	{
		std::cerr << "Error: Could not create file '" << outputFilename << "'" << std::endl;
		inputFile.close();
		return 1;
	}

	// Read and replace line by line
	std::string line;
	while (std::getline(inputFile, line))
	{
		outputFile << replaceAll(line, s1, s2);
		if (!inputFile.eof())
			outputFile << std::endl;
	}

	// Close files
	inputFile.close();
	outputFile.close();

	std::cout << "File created: " << outputFilename << std::endl;

	return 0;
}
