#define BOOST_LOG_DYN_LINK 1 

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

int main( int argc , char* argv[] ){
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  BOOST_LOG_TRIVIAL(error) << "An error severity message";
  BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

  // Filtering can also be applied
  // using namespace boost::log;

  boost::log::core::get()->set_filter
    (   
     boost::log::trivial::severity >= boost::log::trivial::info
    );  

  // Now the first two lines will not pass the filter
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  BOOST_LOG_TRIVIAL(error) << "An error severity message";
  BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
  return 0;
}

