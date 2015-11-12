//#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <glib.h>

int main(int ac, char* av[])
{
    GKeyFile * my_key_file = g_key_file_new();
    GError * error;
    GKeyFileFlags gkff;
    const gchar * configFileName = "./example-config.ini";
    my_key_file=g_key_file_ref(my_key_file);
    g_key_file_load_from_file(my_key_file,
        configFileName,
        gkff,
        &error);
    std::cout<<my_key_file;






    return 0;
}
