using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MTA_Parser
{
    class MTAFile
    {
        string name, filePath;
        List<Animation> animations = new List<Animation>();
        int numMesh, numVert, numAnim;
        int[,] animnSec;
    }

    struct dataSet
    {
        float px, py, pz;
        float u, v;
        float nx, ny, nz;
        int[] f;
    }
}
