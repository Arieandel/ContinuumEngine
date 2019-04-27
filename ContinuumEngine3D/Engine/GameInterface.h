#pragma once
#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H


namespace ContinuumEngine3D {

	class GameInterface {
	public:
		GameInterface() {}
		virtual ~GameInterface() {}

		virtual bool Initialize() = 0;
		virtual void Update(const float deltaTime_) = 0;
		virtual void Render() = 0;
		virtual void onCollision() = 0;
	};

}
#endif // !GAMEINTERFACE_H
