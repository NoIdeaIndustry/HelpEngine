#include "Resources/Model.hpp"
#include <fstream>
#include "Utils/Debug.hpp"
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>

using namespace Resources;
using namespace std;
using namespace Core::myMath;
 

Model::Model()
{
	type = Resource::ResourceType::R_MODEL;
	Resource();
}



void Model::Unload()
{
	//cout << "Clearing model" << endl;
	positions.clear();
	normals.clear();
	UVs.clear();
	triangles.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	this->~Model();
}

void Model::Load(const std::string& filepath)
{
	fstream file;
	file.open(filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!file)
		DEBUG_LOGERROR("Error opening file " + filepath);

	vector<string> lines;
	string currentLine;
	for (currentLine; getline(file, currentLine);)
	{
		lines.push_back(currentLine);
	}
	file.close();
	
	positions.push_back(Vec3());
	normals.push_back(Vec3());
	UVs.push_back(Vec2());
	
	// parse file one line at a time
	for (string line : lines)
	{
		switch (line[0])
		{
		case 'v': ParseVertex(line); break;
		case 'f': ParseIndex(line); break;
		default: break;// DEBUG_LOGERROR("OBJ FILE ERROR.");
		}
	}

	BindData();

}

void Model::BindData()
{
	float* vertices = new float[(triangles.size() / 3) * 8];
	int* indices = new int[triangles.size() / 3];

	// Set up vertices array
	for (int i = 0; i < triangles.size() / 3; i++)
	{
		vertices[i * 8] = positions[triangles[i * 3]].x;
		vertices[i * 8 + 1] = positions[triangles[i * 3]].y;
		vertices[i * 8 + 2] = positions[triangles[i * 3]].z;
		vertices[i * 8 + 6] = UVs[triangles[i * 3 + 1]].x;
		vertices[i * 8 + 7] = UVs[triangles[i * 3 + 1]].y;
		vertices[i * 8 + 3] = normals[triangles[i * 3 + 2]].x;
		vertices[i * 8 + 4] = normals[triangles[i * 3 + 2]].y;
		vertices[i * 8 + 5] = normals[triangles[i * 3 + 2]].z;
		indices[i] = i;
	}
	indexCount = triangles.size() / 3;

	// glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (triangles.size() / 3) * 8, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (triangles.size() / 3), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	delete[] vertices;
	delete[] indices;
}

void Model::ParseVertex(const string& line)
{
	size_t charIndex = 2;
	size_t sub = 0;
	switch (line[1])
	{
	case ' ': 
	{
		Vec3 value;
		value.x = stof(line.substr(charIndex), &sub);
		charIndex += sub;
		value.y = stof(line.substr(charIndex), &sub);
		charIndex += sub;
		value.z = stof(line.substr(charIndex), &sub);
		positions.push_back(value);
		break;
	} 
	case 't':
	{
		Vec2 value;
		value.x = stof(line.substr(charIndex), &sub);
		charIndex += sub;
		if (charIndex != line.length() - 2)
		{
			value.y = stof(line.substr(charIndex), &sub);
		}
		
		UVs.push_back(value);
		break;
	}
	case 'n':  
	{
		Vec3 value;
		value.x = stof(line.substr(charIndex), &sub);
		charIndex += sub;
		value.y = stof(line.substr(charIndex), &sub);
		charIndex += sub;
		value.z = stof(line.substr(charIndex), &sub);
		normals.push_back(value);
		break;
	}
	default: DEBUG_LOGERROR("obj invalid");
	}
}

int Mstoi(string str)
{
	if (str == "")
		return 0;
	else
		return stoi(str);
}

void Model::ParseIndex(const string& line)
{
	string curr;
	Vec3 value;
	enum Dim { X, Y, Z };
	Dim dim = X;

	for (int i = 2; i < line.length(); i++)
	{
		switch(line[i])
		{
		case ' ': 
			if (curr == "")
				break;
			switch (dim)
			{
			case X: value.x = Mstoi(curr); break;
			case Y: value.y = Mstoi(curr); break;
			case Z: value.z = Mstoi(curr); break;
			}
			
			triangles.push_back(value.x); 
			triangles.push_back(value.y);
			triangles.push_back(value.z);
			dim = X; 
			curr = "";
			break;
		case '/': 
			switch (dim)
			{
			case X: value.x = Mstoi(curr); dim = Y; break;
			case Y: value.y = Mstoi(curr); dim = Z; break;
			}
		curr = "";
		break;
		default: curr += line[i]; break;
		}
	}
	switch (dim)
	{
	case X: value.x = Mstoi(curr); break;
	case Y: value.y = Mstoi(curr); break;
	case Z: value.z = Mstoi(curr); break;
	}

	triangles.push_back(value.x); triangles.push_back(value.y); triangles.push_back(value.z); dim = X; curr = ""; 
}


