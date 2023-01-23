#pragma once
#include "../base/Object.h"
#include "../scene/AddList.h"

//�I�u�W�F�N�g�p���G�t�F�N�g�N���X(�C�����C���֐�)
class Camera : public Object {

public:

	Camera();

	//����
	enum Angle {
		non,
		left,
		right
	};
	Angle angle;

	//���W
	float posDistanceX;
	float posDistanceY;
	float moveValue;

	virtual void finalize();//�I���E�������
	virtual void update();//�X�V����
	virtual void draw();//�`�揈��
};
