#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../../headers/camera/Camera.h"
#include "../../headers/camera/ArcBallCamera.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2


class Obj_Loader
{

	public:
		Obj_Loader();

		void drawObj(GLfloat* model, GLfloat* view, GLfloat* proj);

		void loadObj(std::string mesh_dir, std::string vertex_shader, std::string fragment_shader);

	private:

		bool TexcoordsLoaded, NormalsLoaded;
		GLuint VaoId, ProgramId;
		GLint ModelMatrix_UId, ViewMatrix_UId, ProjectionMatrix_UId;

		const std::string read(const std::string& filename);

		const GLuint checkCompilation(const GLuint shader_id, const std::string& filename);

		void checkLinkage(const GLuint program_id);

		const GLuint addShader(const GLuint program_id, const GLenum shader_type, const std::string& filename);

		void createShaderProgram(std::string& vs_file, std::string& fs_file);

		void destroyShaderProgram();

		void parseVertex(std::stringstream& sin);

		void parseTexcoord(std::stringstream& sin);

		void parseNormal(std::stringstream& sin);

		void parseFace(std::stringstream& sin);

		void parseLine(std::stringstream& sin);

		void loadMeshData(std::string& filename);

		void processMeshData();

		void freeMeshData();

		const void createMesh(std::string& filename);

		void createBufferObjects();

		void destroyBufferObjects();
};

