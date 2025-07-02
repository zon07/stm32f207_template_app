[Таблица ниже является заголовком документа]:#
<div class="table-responsive"
  style="width: 100%; border-collapse:collapse; border-spacing:0; text-align: center;">
  <table>
	<tbody>
		<tr>
			<td style="border: 1px solid gray; width: 20%; text-align: center;">
        <p>Агроцифра</p>
      </td>
      <td colspan="2" style="
        border: 1px solid gray; width: 50%">
        <p>Библиотеки BSW</p>
        <p></p>
      </td>
			<td style="border: 1px solid gray; width: 30%; text-align: center;">
        <p>Электронный документ</p>
      </td>
		</tr>
		<tr>
			<td style="border: 1px solid gray; width: 30%; text-align: center;">
        <p>Номер:</p>
      </td>
			<td style="border: 1px solid gray; text-align: center;">
        <p>bsw_libs</p></td>
			<td style="border: 1px solid gray; text-align: center;">
        <p>Версия:</p>
      </td>
			<td style="border: 1px solid gray; width: 30%; text-align: center;">
        <p>A00</p>
      </td>
		</tr>
	</tbody>
</table></div>

[Основной текст документа]:#

**Библиотеки для взаимодействия в периферией блоков управления:**
- БУ702 
- ДБК10

## 1. Структура
```
Блоки: bswCommon, bswBu702, bswDbk10 основанны на функциях bswApi.

bswLibs
├── bswApi          // Функции-интерфейсы для взаимодействия с "нижним-уровнем ПО"
├── bswBu702        // Специфичные функции для работы с блоком БУ702
├── bswCommon       // Общие функции, подходящие ко всем блокам 
├── bswDbk10        // Специфичные функции для работы с блоком БУ702
├── sharedtypes     // Общие типы/словари данных
├── bswLibDic.sldd  // Словарь данных для библиотек bsw
├──.gitignore
├──.gitmodules
├── README.md
└── configBswLibsPaths.m   // Функция для вызова в "стартап" для matlab, уберет ненужные пути
```
