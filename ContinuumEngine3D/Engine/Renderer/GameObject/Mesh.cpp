#include "Mesh.h"


namespace ContinuumEngine3D {


	Mesh::Mesh(SubMesh subMesh_, std::map<std::string, GLuint> shaderPrograms_) : VAO(0), VBO(0), meshVAO(0), meshVBO(0) {

		shaderPrograms = shaderPrograms_;
		subMesh = subMesh_;
		GenerateBuffers();
	}


	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &meshVAO);
		glDeleteBuffers(1, &meshVBO);
		//glDeleteFramebuffers(1, &hdrFBO);
		//glDeleteRenderbuffers(1, &rboDepth);
		//glDeleteFramebuffers(2, pingpongFBO);
		//delete other framebuffers

	}

	void Mesh::GenerateBuffers() {
			if (subMesh.isParallax == false) {
				if (subMesh.isGlowing == false) {
					glDeleteVertexArrays(1, &meshVAO);
					glDeleteBuffers(1, &meshVBO);
					glGenVertexArrays(1, &meshVAO);
					glGenBuffers(1, &meshVBO);
					glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
					glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW); //sizeof(subMesh.vertexList)
					glBindVertexArray(meshVAO);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);

					modelLoc = glGetUniformLocation(shaderPrograms["baseShader"], "model");
					viewLoc = glGetUniformLocation(shaderPrograms["baseShader"], "view");
					projLoc = glGetUniformLocation(shaderPrograms["baseShader"], "proj");
					textureLoc = glGetUniformLocation(shaderPrograms["baseShader"], "inputTexture");
					viewPositionLoc = glGetUniformLocation(shaderPrograms["baseShader"], "viewPosition");//viewPosition
					lightPosLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightPos");
					lightAmbientLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.ambient");
					lightDiffuseLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.diffuse");
					lightColourLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightColor");
				}
				else {
					modelLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "model");
					viewLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "view");
					projLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "proj");
					textureLoc = glGetUniformLocation(shaderPrograms["baseShader"], "inputTexture");
					viewPositionLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "viewPosition");
					//lightPosLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightPos");
					//lightAmbientLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.ambient");
					//lightDiffuseLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.diffuse");
					//lightColourLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightColor");
				}
			}
			else {
				glDeleteVertexArrays(1, &meshVAO);
				glDeleteBuffers(1, &meshVBO);
				glGenVertexArrays(1, &meshVAO);
				glGenBuffers(1, &meshVBO);
				glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
				glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW); //sizeof(subMesh.vertexList)
				glBindVertexArray(meshVAO);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				modelLoc = glGetUniformLocation(shaderPrograms["ParallaxShader"], "model");
				viewLoc = glGetUniformLocation(shaderPrograms["ParallaxShader"], "view");
				projLoc = glGetUniformLocation(shaderPrograms["ParallaxShader"], "proj");
				textureLoc = glGetUniformLocation(shaderPrograms["ParallaxShader"], "ParallaxTexture");

			}

	}


	void Mesh::RenderMesh() {
		glGenVertexArrays(1, &meshVAO);
		glGenBuffers(1, &meshVBO);
		glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
		glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW); //sizeof(subMesh.vertexList)
		glBindVertexArray(meshVAO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(meshVAO);
		glDrawArrays(GL_QUADS, 0, subMesh.vertexList.size());
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &meshVAO);
		glDeleteBuffers(1, &meshVBO);

	}
	void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_, const std::string& shaderProgram_) {

		if (shaderProgram_ == "glowShader") {
			glUseProgram(shaderPrograms["bloomShader"]);
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

			glBindTexture(GL_TEXTURE_2D, subMesh.textureID);
			// set lighting uniforms
			for (unsigned int i = 0; i < camera_->GetLightSources().size(); i++)
			{
				const std::string Lpos = "lights[" + std::to_string(i) + "].Position";
				const std::string Lcolor = "lights[" + std::to_string(i) + "].Color";
				glUniform3fv(glGetUniformLocation(shaderPrograms["bloomShader"], Lpos.c_str()), 1, &camera_->GetLightSources()[i]->GetPosition()[0]);
				glUniform3fv(glGetUniformLocation(shaderPrograms["bloomShader"], Lcolor.c_str()), 1, &camera_->GetLightSources()[i]->GetLightColour()[0]);
			}

			glUniform3fv(glGetUniformLocation(shaderPrograms["bloomShader"], "viewPosition"), 1, &camera_->GetPosition()[0]);

			for (int i = 0; i < instances_.size(); i++) {
				glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["bloomShader"], "model"), 1, GL_FALSE, glm::value_ptr(instances_[i]));
				RenderMesh();
			}

		}

		else if (shaderProgram_ == "ParallaxShader") {

			glUseProgram(shaderPrograms["ParallaxShader"]);
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

			glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

			for (int i = 0; i < instances_.size(); i++) {
				glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["ParallaxShader"], "model"), 1, GL_FALSE, glm::value_ptr(instances_[i]));
				RenderMesh();
			}

		}

		else if (shaderProgram_ == "baseShader") {

			glUseProgram(shaderPrograms["baseShader"]);
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
			glBindTexture(GL_TEXTURE_2D, subMesh.textureID);
			glUniform3fv(glGetUniformLocation(shaderPrograms["baseShader"], "viewPosition"), 1, &camera_->GetPosition()[0]);

			for (int i = 0; i < instances_.size(); i++) {
				glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["baseShader"], "model"), 1, GL_FALSE, glm::value_ptr(instances_[i]));
				RenderMesh();
			}
		}


	}

}