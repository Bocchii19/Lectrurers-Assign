#ifndef FUNCTION_H
#define FUNCTION_H

#include "TKB.h"
#include "GV.h"
#include <string>
#include <vector>
#include <unordered_map>

bool isTimeConflict(const std::string& day1, const std::string& time1, const std::string& day2, const std::string& time2);

bool assignBestTeacher(SubjectTable& subject, std::vector<Teacher>& listTeacher, std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& teacherSchedule);

void writeScheduleToFile(const std::vector<SubjectTable>& listSubject);

std::vector<std::vector<std::string>> readFile(const std::string& file_name);

void writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data);

void editFile(const std::string& file_name, int row, int col, const std::string& newValue);

void printMatchingRows(const std::vector<std::vector<std::string>>& data, int col, std::string value);

void printFile(const std::string& file_name);

#endif
