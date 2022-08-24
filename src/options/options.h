#ifndef HONEY_OPTIONS_H
#define HONEY_OPTIONS_H

struct honey_options {
	const char *script_file; // main entry point
};

enum outcomes_t {
	CONTINUE_SUCCESS,
	EXIT_SUCCESS,
	EXIT_FAILURE,
};

enum outcomes_t parse_options(struct honey_options *options, int argc, char **argv);

#endif
