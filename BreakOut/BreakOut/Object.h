
#ifndef OBJECT_H_
# define OBJECT_H_

class Object
{

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Init() = 0;
	virtual void Draw() = 0;
};

#endif