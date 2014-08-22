// refer to http://stackoverflow.com/questions/2368384/write-a-c-program-to-measure-time-spent-in-context-switch-in-linux-os
// Compile with g++ latencybench.cc -o latencybench -lboost_thread-mt
// Should also work on MSVC and other platforms supported by Boost.

#include <boost/format.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>
#include <algorithm>
#include <cstdlib>
#include <csignal>

volatile bool m_quit = false;

extern "C" void sighandler(int) {
    m_quit = true;
}

std::string num(unsigned val) {
    if (val == 1) return "one occurrence";
    return boost::lexical_cast<std::string>(val) + " occurrences";
}

int main(int argc, char** argv) {
    using namespace boost::posix_time;
    std::signal(SIGINT, sighandler);
    std::signal(SIGTERM, sighandler);
    time_duration duration = milliseconds(10);
    if (argc > 1) {
        try {
            if (argc != 2) throw 1;
            unsigned ms = boost::lexical_cast<unsigned>(argv[1]);
            if (ms > 1000) throw 2;
            duration = milliseconds(ms);
        } catch (...) {
            std::cerr << "Usage: " << argv[0] << " milliseconds" << std::endl;
            return EXIT_FAILURE;
        }
    }
    typedef std::map<long, unsigned> Durations;
    Durations durations;
    unsigned samples = 0, wrongsamples = 0;
    unsigned max = 0;
    long last = -1;
    std::cout << "Measuring actual sleep delays when requesting " << duration.total_milliseconds() << " ms: (Ctrl+C when done)" << std::endl;
    ptime begin = boost::get_system_time();
    while (!m_quit) {
        ptime start = boost::get_system_time();
        boost::this_thread::sleep(start + duration);
        long actual = (boost::get_system_time() - start).total_milliseconds();
        ++samples;
        unsigned num = ++durations[actual];
        if (actual != last) {
            std::cout << "\r  " << actual << " ms " << std::flush;
            last = actual;
        }
        if (actual != duration.total_milliseconds()) {
            ++wrongsamples;
            if (num > max) max = num;
            std::cout << "spike at " << start - begin << std::endl;
            last = -1;
        }
    }
    if (samples == 0) return 0;
    std::cout << "\rTotal measurement duration:  " << boost::get_system_time() - begin << "\n";
    std::cout << "Number of samples collected: " << samples << "\n";
    std::cout << "Incorrect delay count:       " << wrongsamples << boost::format(" (%.2f %%)") % (100.0 * wrongsamples / samples) << "\n\n";
    std::cout << "Histogram of actual delays:\n\n";
    unsigned correctsamples = samples - wrongsamples;
    const unsigned line = 60;
    double scale = 1.0;
    char ch = '+';
    if (max > line) {
        scale = double(line) / max;
        ch = '*';
    }
    double correctscale = 1.0;
    if (correctsamples > line) correctscale = double(line) / correctsamples;
    for (Durations::const_iterator it = durations.begin(); it != durations.end(); ++it) {
        std::string bar;
        if (it->first == duration.total_milliseconds()) bar = std::string(correctscale * it->second, '>');
        else bar = std::string(scale * it->second, ch);
        std::cout << boost::format("%5d ms | %s %d") % it->first % bar % it->second << std::endl;
    }
    std::cout << "\n";
    std::string indent(30, ' ');
    std::cout << indent << "+-- Legend ----------------------------------\n";
    std::cout << indent << "|  >  " << num(1.0 / correctscale) << " (of " << duration.total_milliseconds() << " ms delay)\n";
    if (wrongsamples > 0) std::cout << indent << "|  " << ch << "  " << num(1.0 / scale) << " (of any other delay)\n";
}

