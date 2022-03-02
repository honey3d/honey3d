#include <stdio.h>
#include <unistd.h> /* todo: create windows-compatible alternative */

#include "options/honey_options.h"


static void print_usage(const char *program_name)
{
   printf("Usage: %s [OPTIONS]\n"
	  "  -v         Increase output verbosity (-vvv displays every log message)\n"
	  "  -q         Decrease output verbosity (-qqq suppresses even fatal errors)\n"
	  "  -h         Print this help message and exit\n"
	  "  -s SCRIPT  Load SCRIPT as the entry point instead of 'main.lua'\n",
	  program_name);
}


int parse_options(struct honey_options *opts, int argc, char **argv)
{
   opts->main_script = "main.lua";
   opts->log_level = WARN;
   opts->display_help = 0;

   int opt;
   const char *flags = "hqvs:";
   while ((opt = getopt(argc, argv, flags)) != -1) {
      switch (opt) {
      case 'q':
	 opts->log_level -= 1;
	 break;

      case 'v':
	 opts->log_level += 1;
	 break;

      case 'h':
	 print_usage(argv[0]);
	 opts->display_help = 1;
	 return 1;

      case 's':
	 opts->main_script = optarg;
	 break;

      default:
	 print_usage(argv[0]);
	 return 0;
      }
   }

   honey_log_set_level(opts->log_level);
   honey_log_set_file(stderr);

   return 1;
}
