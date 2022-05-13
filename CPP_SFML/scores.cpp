#include "scores.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <io.h>

scores::scores(std::string file_path, const char separator) : m_file_path(file_path), m_separator(separator) {}

void scores::append_score(std::string nickname, std::string difficulty, unsigned int score) {
	if (_access(m_file_path.c_str(), 0) == 0) {
		m_file_stream.open(m_file_path, std::ios::app);

		if (m_file_stream.is_open() == true) {	
			m_file_stream << '\n' << '\"' << nickname << '\"' << m_separator << '\"' << difficulty << '\"' << m_separator << '\"' << score << '\"';
			m_file_stream.close();

			m_scores.emplace_back(std::make_tuple(nickname, difficulty, score));
			m_scores_sorted = false;
		}

	} else {
		m_file_stream.open(m_file_path, std::ios::out);

		if (m_file_stream.is_open() == true) {
			m_file_stream << '\"' << nickname << '\"' << m_separator << '\"' << difficulty << '\"' << m_separator << '\"' << score << '\"';
			m_file_stream.close();

			m_scores.emplace_back(std::make_tuple(nickname, difficulty, score));
			m_scores_sorted = false;
		}
	}
}

void scores::load_scores() {
	m_file_stream.open(m_file_path, std::ios::in);

	if (m_scores.empty() == false) m_scores.clear();

	if (m_file_stream.is_open() == true) {
		std::string line;

		while (std::getline(m_file_stream, line)) {
			
			std::string nickname;
			std::string difficulty;
			unsigned int score;

			std::string cell;
			unsigned short cell_counter = 0;
			std::istringstream string_stream(line);
			while (std::getline(string_stream, cell, m_separator)) {
				cell_counter++;

				if (cell[0] == '\"') cell = cell.substr(1, cell.size() - 2);

				switch (cell_counter) {
					case 1: nickname = cell;
							break;

					case 2: difficulty = cell;
							break;

					case 3: score = std::stoul(cell);
							break;
					
				}

			}

			m_scores.emplace_back(std::make_tuple(nickname, difficulty, score));

		}
		
		m_file_stream.close();
		m_scores_sorted = false;
		m_all_scores_were_loaded = true;
	}

}

void scores::sort_scores_desc() {
	if (m_scores_sorted == false) {
		if (m_all_scores_were_loaded == false) this->load_scores();
		std::sort(m_scores.begin(), m_scores.end(), [](trio& a, trio& b) { return std::get<2>(a) > std::get<2>(b); });
		m_scores_sorted = true;

	}

}

const unsigned int scores::get_highest_score() {
	if (_access(m_file_path.c_str(), 0) == 0) {
		if (m_all_scores_were_loaded == false) this->load_scores();
		this->sort_scores_desc();
		return std::get<2>(m_scores[0]);

	} else {
		return 0;

	}

}

const trio& scores::operator[](size_t index) {
	try {
		if (index < m_scores.size()) return m_scores[index];
		else throw "\nError: Scores vector index out of range.";

	} catch (const char* error_message) {
		std::cout << error_message;
		exit(EXIT_FAILURE);
	}

}