#pragma once

#include <D3DX10math.h>

#include "../GameplayFoundations/GameObject.h"
#include "..\Resources\MTModel.h"

namespace Actors
{
	enum FOODTYPE
	{
		NORMAL,
		SPECIAL,
		POWERUPS,
		//COUNT
	};

	class Food : public GameplayFoundations::GameObject
	{
	private:
		Resources::MTModel::ptr m_model;
	
		UINT m_score;

		FOODTYPE m_type;

		D3DXVECTOR3 toPos(GameplayFoundations::CellIndex const& _index) const;

	public:
		Food(Resources::MTModel::ptr _model, GameplayFoundations::CellIndex _pos, FOODTYPE _type);
		virtual ~Food();

		void init();
		void update(float _deltaTime);
		void draw(Graphics::dxManager* _dxManager);

		void foodType(FOODTYPE _type);

		UINT getScore();
		FOODTYPE getType();
	};
}