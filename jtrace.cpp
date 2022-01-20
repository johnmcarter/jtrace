/*
 * John Carter
 * Created: 2022/01/19 10:16:41
 * Last modified: 2022/01/20 08:37:35
 */

#include "jtrace.h"


void open_trace() {
    trace_pipe_stream.open( FTRACE_DIR + TRACE_PIPE );
}


void close_trace() {
    trace_pipe_stream.close();
}


int read_trace(std::string output_file) {
    int rc = 0;
    std::string data = "";

    while (1) {
        if ( trace_pipe_stream.is_open() && !trace_pipe_stream.eof() ) {
            std::getline(trace_pipe_stream, data);
            write_trace(output_file, data);
        } else if (!trace_pipe_stream.is_open()) {
            std::cerr << error << "The trace pipe stream isn't open" << std::endl;
            exit(1);
        } else {
            std::cerr << error << "EOF encountered in trace pipe stream" << std::endl;
            exit(1);
        }
    }

    return rc;
}


void write_trace(std::string output_file, std::string data) {
    // Write a well-formed trace to the output stream
    std::string syscall_record;

    output_stream.open(output_file, std::fstream::out | std::fstream::app);
    syscall_record = format_record(data);
    output_stream << syscall_record << "\n";
    output_stream.close();

}


void write_bad_trace(std::string data) {
    // Write a well-formed trace to the output stream

    bad_output_stream.open(error_log, std::fstream::out | std::fstream::app);
    bad_output_stream << data << "\n";
    bad_output_stream.close();

}


std::string format_record(std::string data) {
    // Prints syscall record to file in format:
    // PROCESS_NAME | PID | TIMESTAMP | SYSCALL_NUMBER
    char d1 = ' ';
    char d2 = '-';
    std::ostringstream os;
    std::string formatted_record = "";

    std::vector<std::string> syscall_record = split(data, d1);

    if (syscall_record.size() == 13) {
        std::vector<std::string> name_and_pid = split(syscall_record.at(0), d2);
        std::string process_name = name_and_pid.at(0);
        std::string pid = name_and_pid.at(1);
        std::string timestamp = syscall_record.at(3);
        timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), ':'), timestamp.end());
        std::string number = syscall_record.at(6);

        os << process_name << "," << pid << "," << timestamp << "," << number;
        formatted_record = os.str();
    } else {
        write_bad_trace(data);
    }

    return formatted_record;
}


void print_usage(char **argv) {
    std::cout << "USAGE: " << std::endl;
    std::cout << argv[0] << " <output file>" << std::endl;
}


int main(int argc, char **argv) {
    std::cout << std::endl;
    std::cout << "\033[1;36mjtrace: the new and improved syscall-sensor.\033[0m" << std::endl << std::endl;

    if (argc == 2) {
        std::cout << info << "You chose to print to " << argv[1] << std::endl;
    } else {
        std::cerr << error << "Incorrect number of input arguments" << std::endl << std::endl;
        print_usage(argv);
        exit(1);
    } 
    
    open_trace();
    if (!trace_pipe_stream.is_open()) {
        std::cerr << error << "Failed to open trace pipe stream. You may need root privileges." << std::endl;
    } else {
        read_trace(argv[1]);
        close_trace();
    }

    return 0;
}