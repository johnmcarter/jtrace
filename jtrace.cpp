/*
 * John Carter
 * Created: 2022/01/19 10:16:41
 * Last modified: 2022/01/20 15:46:38
 */

#include "jtrace.h"


void read_trace(std::string output_file) {
    // Read traces from trace_pipe variable and send them to be logged
    std::string data = "";

    while (trace_pipe_stream.is_open() && !trace_pipe_stream.eof() ) {
        std::getline(trace_pipe_stream, data);
        write_trace(output_file, data);
    }
    
}


void write_trace(std::string output_file, std::string data) {
    // Write a well-formed trace to the output stream

    output_stream.open(output_file, std::fstream::out | std::fstream::app);
    output_stream << format_record(data) << "\n";
    output_stream.close();

}


std::string format_record(std::string data) {
    // Prints syscall record to file in format:
    // PROCESS_NAME | PID | TIMESTAMP | SYSCALL_NUMBER
    char d1 = ' ';
    char d2 = '-';
    std::ostringstream os;

    std::vector<std::string> syscall_record = split(data, d1);

    if (syscall_record.size() == 13) {
        std::vector<std::string> name_and_pid = split(syscall_record.at(0), d2);
        std::string timestamp = syscall_record.at(3);
        std::string number = syscall_record.at(6);
        timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), ':'), timestamp.end());

        os << name_and_pid.at(0) << "," << name_and_pid.at(1) << "," << timestamp << "," << number;
        return os.str();
    } else {
        return "ERROR: " + data;
    }

}


void print_usage() {
    std::cout << "USAGE: " << std::endl;
    std::cout << "jtrace <output file>" << std::endl;
}


int main(int argc, char **argv) {
    std::cout << std::endl;
    std::cout << "\033[1;36mjtrace: the new and improved syscall-sensor.\033[0m" << std::endl << std::endl;


    if (argc == 2) {
        std::string arg1(argv[1]);
        if (arg1 == "-h" || arg1 == "--help") {
            print_usage();
        } else {
            std::cout << info << "You chose to print to " << arg1 << std::endl;

            // open the trace pipe stream and try to read from it
            trace_pipe_stream.open( FTRACE_DIR + TRACE_PIPE );
            if (trace_pipe_stream.is_open()) {
                read_trace(arg1);
                trace_pipe_stream.close();
            } else {
                std::cerr << error << "Failed to open trace pipe stream. Are you root?" << std::endl;
            }
        }
    } else {
        std::cerr << error << "Incorrect number of input arguments" << std::endl << std::endl;
        print_usage();
    } 

    return 0;
}