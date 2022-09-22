#include "test/honey-test.h"
#include "import.test.h"

void suite_import()
{
	lily_run_test(test_push_vector);
	lily_run_test(test_push_face);
	lily_run_test(test_push_aistring);

	lily_run_test(test_push_mesh);
	lily_run_test(test_push_mesh_faces);
	lily_run_test(test_push_mesh_normals);
	lily_run_test(test_push_mesh_tangents);
	lily_run_test(test_push_mesh_uvs);

	lily_run_test(test_push_node);
}
