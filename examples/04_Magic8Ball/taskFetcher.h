#ifndef TASK_FETCHER_H
#define TASK_FETCHER_H

#include <vector>
#include <Arduino.h>

extern const char* serverURL;
extern std::vector<String> tasks; 
void autoFetchEvery(unsigned long  intervalMs);
void fetchTasks(const char* serverURL);

#endif
