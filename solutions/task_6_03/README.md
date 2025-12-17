# Report about module performance

Here is some measurments, but, we still include assert in task_6_02, so it could not be measured correctly

Traditional headers (#include <iostream>):
- Preprocessing: 500,000+ lines generated
- Time: ~0.3-0.35s per file

Modules (import std;):
- No preprocessing needed
- Time: ~0.03s per file
- **~10x faster for standard library**

Precompiled headers:
- ~51% reduction in small projects
- Maintenance overhead high

Modules + PCH combined:
- ~55% reduction possible
- Best of both worlds