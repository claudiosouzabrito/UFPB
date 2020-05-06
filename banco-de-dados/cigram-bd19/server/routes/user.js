const Router = require('express-promise-router')
const db = require('../db')
const uuidv1 = require("uuid/v1")

const router = new Router()

module.exports = router

/********************************************************************************
*
*   Create a user
*   Method: POST
*   Payload Type: json 
*   Payload Content: email, username, senha, nomereal, biografia, privacidade
*
*********************************************************************************/

router.post('/create', async  (req, res) => {
    user = req.body;
    command = "INSERT INTO usuario (ID, email, username, senha, nomereal, biografia, privacidade) VALUES ($1, $2, $3, $4, $5, $6, $7)";
    values = [uuidv1(), user.email, user.username, user.senha, user.nomereal, user.biografia, user.privacidade];

    await db.query(command, values).then(() => res.send("User created")).catch((err) => {
        res.status(400).send(`Error when creating users`)
    });
})


/*************************************************
*
*   Search users by username
*   Method: GET
*   Params: username
*
***************************************************/

router.get('/:username', async  (req, res) => {
    const { username } = req.params;

    const query = `SELECT * FROM usuario WHERE username = '${username}';`;
    await db.query(query, []).then((row) => {
        // Checking if array is empty:
        if(!Array.isArray(row.rows) || !row.rows.length) {
            throw new Error("User not found"); return
        };
        let {username, nomereal, biografia, privacidade} =  row.rows[0]
        if(req.session.user !== username && privacidade == true)
            res.status(403).send({username, privacidade:true});
        let result = {username, nomereal, biografia, privacidade};
        res.send(result);
    }).catch((err) => {
        res.status(404).send(`${err}`);
    });
})

/*************************************************
*
*   Search users by pattern
*   Method: GET
*   Params: pattern
*
*********************************************************/

router.get('/search/:pattern', async  (req, res) => {
    const pattern = req.params.pattern;
    if(req.session.user){
        const findUser = `SELECT usuario.id, usuario.username, usuario.nomereal FROM usuario WHERE usuario.id != '${req.session.userId}' AND usuario.username LIKE '%${pattern}%' OR usuario.nomereal LIKE '%${pattern}%' or usuario.biografia LIKE '%${pattern}%'`;
        await db.query(findUser , []).then((row) => res.send(row.rows)).catch((err)=>{
            res.status(400).send(err);
        });
    }else{
        res.status(403).send("Not logged in")
    }
})