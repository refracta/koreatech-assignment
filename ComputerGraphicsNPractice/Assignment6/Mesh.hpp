#pragma  once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <gl/glut.h>
#include "glk.h"

using namespace std;

struct Vertex {         // Vertex: x, y, z 의 위치값
    float x, y, z;
};

struct Face {           // Face: vertex 3개의 인덱스
    int vi[3];
};

struct Normal {         // Normal: face와 세 정점의 법선벡터
    float norFace[3];
    float norV1[3], norV2[3], norV3[3];
};

class Mesh {        // Mesh 클래스
    int nVtx = 0;   // Vertex 개수
    Vertex *vertex = NULL;
    int nFace = 0;
    Face *face = NULL;
    Normal *normal = NULL;
public:
    Mesh() {}

    ~Mesh() { clearAse(); }

    void clearAse() { // -> vertex, face, normal 리스트의 동적할당 해제하는
        if (nVtx != 0)
            delete[] vertex;
        if (nFace != 0) {
            delete[] face;
            delete[] normal;
        }
        nVtx = nFace = 0;
    }

    void readAse(const char *fileName) { // ASE file load
        FILE *fp;
        char line[256], str[40];         // 한 라인과 문자열 버퍼
        float _x, _y, _z;
        int num = 0;

        if ((fp = fopen(fileName, "r")) == NULL) {
            cout << "File not found." << endl;
            return;
        }
        while (fgets(line, 256, fp) != NULL) {
            sscanf(line, "%s", str);
            if (strcmp(str, "*MESH") == 0) {                  // "*MESH"라는 문자가 나올 때까지
                fgets(line, 256, fp);   // *TIMEVALUE
                fgets(line, 256, fp);   // *MESH_NUMBERTEX
                sscanf(line, "%s%d", str, &nVtx);
                fgets(line, 256, fp);   // *MESH_NUMFACES
                sscanf(line, "%s %d", str, &nFace);

                vertex = new Vertex[nVtx];  // vertex 리스트 동적할당
                face = new Face[nFace];     // face 리스트 동적할당
                normal = new Normal[nFace]; // normal 리스트 동적할당

                fgets(line, 256, fp);
                sscanf(line, "%s", str);
                if (strcmp(str, "*MESH_VERTEX_LIST") == 0) {
                    for (int i = 0; i < nVtx; i++) { // vertex 의 x, y, z
                        fgets(line, 256, fp);
                        sscanf(line, "%s%d%f%f%f", str, &num, &_x, &_y, &_z);
                        vertex[i].x = _x;
                        vertex[i].y = _y;
                        vertex[i].z = _z;
                    }
                }
                fgets(line, 256, fp); // Read the Line '}'
                fgets(line, 256, fp); // Read the Line *MESH_FACE_LIST
                sscanf(line, "%s", str);
                if (strcmp(str, "*MESH_FACE_LIST") == 0) {
                    for (int i = 0; i < nFace; i++) {
                        fgets(line, 256, fp);
                        sscanf(line, "%s%s%s%d%s%d%s%d%s%d%s%d%s%d%s",
                               str, str, str, &(face[i].vi[0]),
                               str, &(face[i].vi[1]),
                               str, &(face[i].vi[2]),
                               str, &num,
                               str, &num,
                               str, &num,
                               str);
                    }
                }

                fgets(line, 256, fp);    // Read the Line '}'
                fgets(line, 256, fp); // Read the Line *MESH_NUMCVERTEX --->
                sscanf(line, "%s", str);

                if (strcmp(str, "*MESH_NUMCVERTEX") == 0) { // 내용이 *MESH
                    fgets(line, 256, fp); // 다시 *MESH_NORMALS 를 위한
                    sscanf(line, "%s", str);
                }

                if (strcmp(str, "*MESH_NORMALS") == 0) {
                    for (int i = 0; i < nFace; i++) {
                        float *nF = normal[i].norFace;
                        float *nV1 = normal[i].norV1;
                        float *nV2 = normal[i].norV2;
                        float *nV3 = normal[i].norV3;

                        fgets(line, 256, fp);            // Read the Line *MESH_FACENORM
                        sscanf(line, "%s%d%f%f%f", str, &num, nF, nF + 1, nF + 2);

                        fgets(line, 256, fp);            // Read the Line *MESH_VERTEXN
                        sscanf(line, "%s%d%f%f%f", str, &num, nV1, nV1 + 1, nV1 + 2);
                        fgets(line, 256, fp);         // Read the Line *MESH_VERTEXN
                        sscanf(line, "%s%d%f%f%f", str, &num, nV2, nV2 + 1, nV2 + 2);
                        fgets(line, 256, fp);         // Read the Line *MESH_VERTEXN
                        sscanf(line, "%s%d%f%f%f", str, &num, nV3, nV3 + 1, nV3 + 2);
                    }
                }
                break;
            }
        }
        fclose(fp);
    }

    void draw(float scale = 1.0f, bool bCoord = false) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < nFace; i++) {
            Vertex *v1 = &vertex[face[i].vi[0]];
            Vertex *v2 = &vertex[face[i].vi[1]];
            Vertex *v3 = &vertex[face[i].vi[2]];
            glNormal3fv(normal[i].norV1);
            glVertex3f(v1->x / scale, v1->z / scale, v1->y / scale);
            glNormal3fv(normal[i].norV2);
            glVertex3f(v2->x / scale, v2->z / scale, v2->y / scale);
            glNormal3fv(normal[i].norV3);
            glVertex3f(v3->x / scale, v3->z / scale, v3->y / scale);
        }
        glEnd();
        if (bCoord)
            glkDrawCoord(1.0);
    }

    void draw(float r, float g, float b, float scale = 1.0f, bool bCoord = false) {
        glkSetColor(r, g, b, 1.0);
        draw(scale, bCoord);
    }
};