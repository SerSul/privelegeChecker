### Содержание
---
1. [Тестовое задание](#task)
2. [Как запустить веб-приложение?](#how-to-run)

### Тестовое задание <a name="task"></a>
Необходимо написать простое web-приложение с использованием node.js+node-addon-api (C++)+WinAPI для проверки привилегии пользователя (например, Администратор/Пользователь/Гость) в списке пользователей операционной системы Windows.

Приложение должно работать по следующему сценарию
 
1. Пользователь запускает web-сервер из корня проекта:
server.bat
2. Автоматически открывается браузер с начальной web страницей, на которой отображаются
- поле ввода имени пользователя
- кнопка "Проверить"
3. Пользователь вводит любое имя пользователя и нажимает на "проверить"
4. Если введённый пользователь в списке пользователей имеет привилегию Администратор/Пользователь/Гость, отображается страница с надписью "Пользователь имя_введённого_пользователя имеет привилегию привилегия_введённого пользователя", иначе "Пользователя имя_введённого_пользователя нет". Под надписью есть кнопка "Назад", при нажатии на которую происходит возврат на начальную страницу.
5. Проверку привилегий осуществлять через WinAPI.

# Как запустить веб-приложение? <a name="how-to-run"></a>

1. **Установите [Node.js](https://nodejs.org/en/download/package-manager) на компьютер.**

   Чтобы убедиться в том, что Node.js работает, выполните следующие команды в командной строке:

   ```sh
   node -v  
   npm -v   

2. **Соберите Node.js аддон.**

   Выполните следующие команды в командной строке:

   ```sh
    npm install -g node-gyp
    npm install node-addon-api express  
    node-gyp configure      
    node-gyp build          

2. **Запустите BAT-файл.**

   Выполните следующую команду в командной строке:

   ```sh
    ./server.bat

После этого веб-приложение будет запущено, и вы сможете открыть браузер и перейти на http://localhost:3000, чтобы использовать его.
