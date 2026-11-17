# Visual Studio — лабораторна робота № 6

Виконав: Бабенко Дмитро Володимирович, група 204-ТН. Варіант 1.

## Відкриття та запуск

Потрібні Visual Studio 2022 або новіша, компонент **Розробка класичних програм мовою C++**, інструменти MSVC для x64 та Windows SDK 10.0 (підійде сучасний Windows 10/11 SDK).

1. Відкрийте `Lab06.sln`, розташований поряд із наявними вихідними файлами репозиторію.
2. Виберіть `Debug` або `Release` та платформу `x64`.
3. Зберіть рішення через **Build Solution** (`Ctrl+Shift+B`).
4. Запустіть консольний проєкт `Lab06Client` без налагодження (`Ctrl+F5`). Він перший у рішенні; якщо Visual Studio зберегла інший стартовий проєкт, виберіть **Set as Startup Project** для цього клієнта.
5. Введіть дані з `input.txt`:

```text
3 4
1 -2
```

Порівняйте вивід із `expected_output.txt`. Успішні самоперевірки позначено `PASS`; код завершення програми — `0`.

## Складання MSBuild

У Developer PowerShell for Visual Studio:

```powershell
msbuild Lab06.sln /m /p:Configuration=Debug /p:Platform=x64
```

Для оптимізованої збірки замініть `Debug` на `Release`. Результат — `x64/Debug/lab06.exe` або `x64/Release/lab06.exe`.

Проєкти використовують C++14 (`stdcpp14`), стандартну обробку винятків `/EHsc` та рівень попереджень `/W4`. `PlatformToolset=v143` відповідає інструментам MSVC Visual Studio 2022. У новішій Visual Studio можна встановити компонент v143 або виконати Retarget Solution до наявного набору інструментів. Для командної збірки інший установлений toolset також можна передати через `/p:PlatformToolset=...`.

## Динамічна бібліотека

`Lab06Complex.vcxproj` складає `complex.dll` і бібліотеку імпорту `complex.lib`; тільки цей проєкт визначає `COMPLEX_EXPORTS`. `Lab06Client.vcxproj` складає `lab06.exe` та імпортує клас із DLL через ProjectReference. DLL і клієнт потрапляють до одного каталогу `x64/Debug` або `x64/Release`, тому DLL доступна під час запуску. Усі проєкти однієї конфігурації використовують однакову DLL-версію CRT (`/MDd` або `/MD`).
