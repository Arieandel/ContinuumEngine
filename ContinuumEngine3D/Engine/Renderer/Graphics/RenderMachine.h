#ifndef RENDERMACHINE_H
#define RENDERMACHINE_H

#include <vector>
#include "../../ContinuumEngine.h"
#include <ContinuumEngine2D/ContinuumEngine2D.h>
#include <ContinuumEngine2D/GUI.h>




namespace ContinuumEngine3D {

	class RenderMachine
	{
	public:
		RenderMachine(const RenderMachine&) = delete;
		RenderMachine(RenderMachine&&) = delete;
		RenderMachine& operator=(const RenderMachine&) = delete;
		RenderMachine& operator=(RenderMachine&&) = delete;

		static RenderMachine* GetInstance();
		void Render(std::vector<Model*> models_, float delta_);



	private:
		RenderMachine();
		~RenderMachine();

		static std::unique_ptr<RenderMachine> RenderMachineInstance;
		friend std::default_delete<RenderMachine>;
		
		float delta;

	};
}
#endif