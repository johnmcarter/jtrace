/*
 * John Carter
 * Created: 2022/01/19 10:16:41
 * Last modified: 2022/01/20 15:45:58
 */

#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

static const std::string FTRACE_DIR =        "/sys/kernel/debug/tracing/";
static const std::string TRACE =             "trace";
static const std::string TRACING_ON =        "tracing_on";
static const std::string RAW_SYSCALLS_DIR =  "raw_syscalls/";
static const std::string SYS_ENTER_DIR =     "sys_enter/";
static const std::string SYS_EXIT_DIR =      "sys_exit/";
static const std::string EVENTS_DIR =        "events/";
static const std::string TRACE_PIPE =        "trace_pipe";
static const std::string CURRENT_TRACER =    "current_tracer";
static const std::string ENABLE =            "enable";
static const std::string NO_TRACE =          "set_ftrace_notrace";
static const std::string FILTER  =           "filter";
static const std::string FILTER_SYS_ENTER =  FTRACE_DIR + EVENTS_DIR + RAW_SYSCALLS_DIR + SYS_ENTER_DIR + FILTER;
static const std::string FILTER_SYS_EXIT =   FTRACE_DIR + EVENTS_DIR + RAW_SYSCALLS_DIR + SYS_EXIT_DIR + FILTER;

static const uint_fast8_t MIN_LENGTH = 50; 

std::ifstream trace_pipe_stream;
std::ofstream output_stream; 

const std::string error = "[\033[31mERROR\033[0m] ";
const std::string info = "[\033[32mINFO\033[0m] ";


void read_trace(std::string output_file);
void write_trace(std::string output_file, std::string data);
void print_usage();
std::string format_record(std::string data);
std::vector<std::string> split(std::string str, char delimiter);