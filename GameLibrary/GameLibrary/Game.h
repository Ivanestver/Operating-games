#pragma once
#ifdef GAME_EXPORTS
#define GAME_API __declspec(dllexport)	
#else
#define GAME_API __declspec(dllimport)	
#endif // GAME_EXPORTS

/// <summary>
/// ����������� ����� ��������� �������
/// </summary>
/// <param name="efficiency">: ������ �������������� ������� �������, ��� r </param>
/// <param name="amount"> : ������ ��������� ������� �������, ��� V </param>
/// <param name="k"> : ����� �������� </param>
/// <return>���������� ����� ��������� ������� � ���������� ��������� � ����������� ���������� wholePotentional</return>
extern GAME_API unsigned long GetWholePotentional(unsigned int *efficiency, unsigned int *amount, unsigned int k);

/// <summary>
/// ����������� ������������� ����� ������������ �������, ��� lambda. ���� ����� �� ������, �� ��������� ��� ����������
/// </summary>
/// <param name="probability"> : ������ ������������ ��������� �� ������������</param>
/// <param name="i"> : ���������� ����������� </param>
/// <returns>���������� ������������� ����� ������������ ������� � ���������� ��������� � ����������� ���������� sumProbability</returns>
extern GAME_API float GetDestroyedMeans(float *probability, unsigned long i);

/// <summary>
/// ��������������� �������
/// </summary>
/// <returns>�� ��, ��� � � �����������</returns>
extern GAME_API float GetDestroyedMeans();

/// <summary>
/// ��������� ��������������� ��������� �������
/// </summary>
/// <param name="attack"> ���������� ������ ���������</param>
/// <returns> ���������� max(0, attack - lambda)</returns>
extern GAME_API float GetBestResult(unsigned long attack);

/// <summary>
/// ����������� ������������� k-��� �������� ������� �� i-�� �����������
/// </summary>
/// <param name="probability">: ����������� �� ������ �����������</param>
/// <param name="amount">: ���������� ������� k-��� ����</param>
/// <returns> ���������� �������������</returns>
extern GAME_API float GetDistribution(float probability, unsigned int amount);