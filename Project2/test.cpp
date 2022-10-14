#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

const std::string wrong_input_message("Error: The specified input file does not exist.");
const std::string wrong_extension_message("Error: The specified input file exists, but is not a PPM file.");
const std::string wrong_transformation_message("Error: The specified transformation does not correspond to any accepted transformations.");

