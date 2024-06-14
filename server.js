const express = require('express');
const path = require('path');
const addon = require('./build/Release/privilege_check.node');

const app = express();
const PORT = 8081;

app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

app.post('/check', (req, res) => {
    const username = req.body.username;
    const privilege = addon.checkUserPrivilege(username);
    res.send(`
        <p>Пользователь ${username} ${privilege === 'нет' ? 'нет' : `имеет привилегию ${privilege}`}</p>
        <button onclick="window.history.back()">Назад</button>
    `);
});

app.listen(PORT, () => {
    console.log(`Запустил сервер по адресу http://localhost:${PORT}`);
});
