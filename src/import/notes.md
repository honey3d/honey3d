tinyobj notes
=============

tinyobjloader-c is not a very well-documented library, so i'm gonna keep some notes
as i figure things out

 * the indices within a vertex_index_t object are not indices into the vertices, normals, or texcoords arrays;
   rather, they are indices to 3-vectors within those arrays. To get actual indices, multiply them by three.
 * "shapes" are individual meshes.
   * a shape's `face_offset` is the *number of faces* into the `faces` array to go before
     you find the data for the current shape, and the length is the *number of faces*.
     This means that they are **NOT** indices to the `faces` array; they are indices/lengths
     in the `face_num_verts` array, which you can then use to determine indices into the
     faces array.
