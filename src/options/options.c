#include <stdio.h>
#include <cargs.h>
#include "options.h"

static struct cag_option opts[] = {
	{
		.identifier = 's',
		.access_letters = "s",
		.access_name = "script",
		.value_name = "SCRIPT_FILE",
		.description = "The filename of the main script. (default: main.lua)"
	},
	{
		.identifier = 'h',
		.access_letters = "h",
		.access_name = "help",
		.value_name = NULL,
		.description = "Shows this help message"
	},
};


void print_help(char *program_name)
{
	printf("usage: %s [OPTIONS]\n", program_name);
	cag_option_print(opts, CAG_ARRAY_SIZE(opts), stdout);
}


enum outcomes_t parse_options(struct honey_options *options, int argc, char **argv)
{
	/* default values */
	options->script_file = "main.lua";

	/* parse options */
	char id;
	const char *value;
	cag_option_context context;

	cag_option_prepare(&context, opts, CAG_ARRAY_SIZE(opts), argc, argv);
	while(cag_option_fetch(&context)) {
		id = cag_option_get(&context);
		switch(id) {
		case 's':
			options->script_file = cag_option_get_value(&context);
			break;
		case 'h':
			print_help(argv[0]);
			return EXIT_SUCCESS;
		default:
			return EXIT_FAILURE;
		}
	}

	return CONTINUE_SUCCESS;
}
