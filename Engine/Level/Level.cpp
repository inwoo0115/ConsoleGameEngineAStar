#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	//actors.PushBack(newActor);
	addRequestedActors.emplace_back(newActor);
}

void Level::ProcessAddedAndDestroyedActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��.
	for (int ix = 0; ix < actors.size();)
	{
		if (actors[ix]->isExpired)
		{
			delete actors[ix];
			actors[ix] = nullptr;
			actors.erase(actors.begin() + ix);
			continue;
		}

		++ix;
	}

	// �߰� ��û�� ���� ó��.
	if (addRequestedActors.size() > 0)
	{
		for (Actor* newActor : addRequestedActors)
		{
			actors.emplace_back(newActor);
		}
		
		addRequestedActors.clear();
	}
}

void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��.
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��.
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Draw();
	}
}

std::vector<std::vector<int>> Level::OpenMapFile(const char* map)
{
	FILE* file = nullptr;

	int error = fopen_s(&file, map, "rb");
	if (error != 0) {
		std::cerr << "Error: Unable to open file. Error code: " << error << std::endl;
		return {};
	}

	//���� �б� + ����ġ�� �̵�
	fseek(file, 0, SEEK_END);
	//�̵��� ��ġ fp ��������
	size_t readSize = ftell(file);
	//fp ����ġ
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	//���� �о ���ۿ� ���
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		return {};
	}

	buffer[readSize] = '\0';

	std::vector<std::vector<int>> grid;

	int i = 0;
	while (i < (int)bytesRead)
	{
		std::vector<int> row;
		while (buffer[i] != '\n' && buffer[i] != '\0')
		{
			row.push_back(buffer[i] - 48);
			++i;
		}
		grid.push_back(row);
		++i;
	}
	fclose(file);
	delete[] buffer;
	return grid;
}
