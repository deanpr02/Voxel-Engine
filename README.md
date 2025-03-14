Voxel Engine [Dat Engine] Version 0.0.0 by Dean Prach

This contains a working log of progress made on this iteration of a voxel engine.

=== March 11, 2025 ===
Initializing the project by getting OpenGL and other dependencies working.

=== March 12, 2025 ===
Initially, I started off by rendering each block individually, which is slow and expensive, so I have now begun implementing a chunking system, where I now only have to call a render method once per 16x16x16 chunk (subject to change). Next on the agenda is to have the world positioning baked into the chunk, and have some chunk retrieval system so I can actually draw multiple chunks onto the screen. Currently, I have the ability to draw one chunk at the world origin (0,0,0). Finally, due to the static nature of terrain, I have moved away from using transformations to move my squares around, I have them baked into the vertices directly since they are not going to be moving in general, if dynamic chunks are needed I can always implement that in the future.


=== March 14, 2025 ===
Added dynamic chunk loading so as you progress in a direction then it will generate new chunks. If the chunk has already been generated before then it will be loaded in.