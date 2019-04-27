#include "Model.h"



namespace ContinuumEngine3D {

	Model::Model(const std::string& objPath_, const std::string& matPath_, const std::string& shaderProgram_, bool isGlowing_, bool isParallax_) : subMeshes(std::vector<Mesh*>()), modelInstances(std::vector<glm::mat4>())
	{
		isGlowing = isGlowing_;
		isParallax = isParallax_;
		name = objPath_;
		if (shaderProgram_ == "glowShader") {
			shaderProgram["bloomShader"] = ShaderHandler::GetInstance()->GetShader("bloomShader");
			shaderProgram["bloomLightShader"] = ShaderHandler::GetInstance()->GetShader("bloomLightShader");
			shaderProgram["blurShader"] = ShaderHandler::GetInstance()->GetShader("blurShader");
			shaderProgram["bloomFinalShader"] = ShaderHandler::GetInstance()->GetShader("bloomFinalShader");
		}

		else if (shaderProgram_ == "SkyboxShader") {
			shaderProgram["SkyboxShader"] = ShaderHandler::GetInstance()->GetShader("SkyboxShader");
		}

		else if (shaderProgram_ == "ParallaxShader") {
			shaderProgram["ParallaxShader"] = ShaderHandler::GetInstance()->GetShader("ParallaxShader");
		}

		obj = new LoadOBJModel();
		obj->LoadModel(objPath_, matPath_, isGlowing, isParallax);
		this->LoadModel();

	}


	Model::~Model()
	{
		if (subMeshes.size() > 0) {
			for (auto m : subMeshes) {
				delete m;
				m = nullptr;
			}
			subMeshes.clear();
			subMeshes.shrink_to_fit();
		}
		modelInstances.clear();
		modelInstances.shrink_to_fit();
	}

	void Model::Render(Camera* camera_, const std::string& shaderProgram_) {
		//glUseProgram(shaderProgram[shaderProgram_]);
		for (auto m : subMeshes) {
			m->Render(camera_, modelInstances, shaderProgram_);
		}
	}

	void Model::AddMesh(Mesh* mesh_) {
		subMeshes.push_back(mesh_);
	}




	GLuint Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
		modelInstances.push_back(GetTransform(position_, angle_, rotation_, scale_));
		return modelInstances.size() - 1;
	}

	void Model::DeleteInstance(GLuint index_) {
		std::cout << "Model instance count: " << modelInstances.size() << "Deleting index: " << index_ << std::endl;
		//std::vector<glm::mat4> TempModelInstances = modelInstances;
		//modelInstances.clear();
		//modelInstances.shrink_to_fit();

		//for (auto instances : TempModelInstances) {
		//	if (instances != TempModelInstances[index_]) {
		//		modelInstances.push_back(instances);
		//	}
		//}
		//TempModelInstances.clear();
		//TempModelInstances.shrink_to_fit();
		//modelInstances.erase(modelInstances.begin() + index_);
		//modelInstances.shrink_to_fit();
		std::cout << "Model instance count: " << modelInstances.size() << std::endl;

	}

	void Model::UpdateInstance(GLuint index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
		modelInstances[index_] = GetTransform(position_, angle_, rotation_, scale_);
	}
	glm::mat4 Model::GetTransform(GLuint index_) const {

		//glm::vec3 pos = glm::vec3(modelInstances[index_][3][0], modelInstances[index_][3][1], modelInstances[index_][3][2]);

		return modelInstances[index_];

	}

	glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const {
		glm::mat4 model;
		model = glm::translate(model, position_);
		model = glm::rotate(model, angle_, rotation_);
		model = glm::scale(model, scale_);

		return model;
	}
	void Model::LoadModel() {
		for (int i = 0; i < obj->GetMeshes().size(); i++) {

			subMeshes.push_back(new Mesh(obj->GetMeshes()[i], shaderProgram));


		}
		BoundaryBox = obj->GetBoundaryBox();
		delete obj;
		obj = nullptr;
	}


	BoundaryBox Model::GetBoundaryBox() {

		return BoundaryBox;
	}

}