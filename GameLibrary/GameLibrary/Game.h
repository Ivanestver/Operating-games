#pragma once
#ifdef GAME_EXPORTS
#define GAME_API __declspec(dllexport)	
#else
#define GAME_API __declspec(dllimport)	
#endif // GAME_EXPORTS

/// <summary>
/// Высчитывает общий потенциал обороны
/// </summary>
/// <param name="efficiency">: Массив эффективностей средств обороны, или r </param>
/// <param name="amount"> : Массив количеств средств обороны, или V </param>
/// <param name="k"> : Длина массивов </param>
/// <return>Возвращает общий потенциал обороны и записывает результат в статическую переменную wholePotentional</return>
extern GAME_API unsigned long GetWholePotentional(unsigned int *efficiency, unsigned int *amount, unsigned int k);

/// <summary>
/// Высчитывает потенциальное число уничтоженных средств, или lambda. Если вызов не первый, то вызывайте без параметров
/// </summary>
/// <param name="probability"> : Массив вероятностей попаданий на направлениях</param>
/// <param name="i"> : Количество направлений </param>
/// <returns>Возвращает потенциальное число уничтоженных средств и записывает результат в статическую переменную sumProbability</returns>
extern GAME_API float GetDestroyedMeans(float *probability, unsigned long i);

/// <summary>
/// Безпараметровый вариант
/// </summary>
/// <returns>То же, что и с параметрами</returns>
extern GAME_API float GetDestroyedMeans();

/// <summary>
/// Наилучший гарантированный результат обороны
/// </summary>
/// <param name="attack"> Количество единиц нападения</param>
/// <returns> Возвращает max(0, attack - lambda)</returns>
extern GAME_API float GetBestResult(unsigned long attack);

/// <summary>
/// Высчитывает распределение k-ого средства обороны на i-ом направлении
/// </summary>
/// <param name="probability">: Вероятность на данном направлении</param>
/// <param name="amount">: Количество средств k-ого типа</param>
/// <returns> Возвращает распределение</returns>
extern GAME_API float GetDistribution(float probability, unsigned int amount);