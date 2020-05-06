const Router = require('express-promise-router')
const db = require('../db')

const router = new Router()

module.exports = router

router.get('/f/:username', async (req, res) => {
    const user = req.params.username;
    if (!req.session.user) res.status(403).send("Not logged in");

    const query = `SELECT id FROM usuario WHERE username = '${user}';`;
    await db.query(query, []).then((row) => {
        // Checking if array is empty:
        if(!Array.isArray(row.rows) || !row.rows.length) {
            throw new Error("User not found");
        };
        let {id} =  row.rows[0];
        db.query("INSERT INTO seguindo (iduser, idseguido) VALUES ($1, $2)", [req.session.userId, id]).then((row) => {
            res.send({user:req.session.userId, following: id})
        }).catch((err) => {
            res.status(404).send(`${err}`);
        });
    }).catch((err) => {
        res.status(404).send(`${err}`);
    });
});

router.get('/un/:username', async (req, res) => {
    const user = req.params.username;
    if (!req.session.user) res.status(403).send("Not logged in");

    const query = `SELECT id FROM usuario WHERE username = '${user}';`;
    await db.query(query, []).then((row) => {
        // Checking if array is empty:
        if(!Array.isArray(row.rows) || !row.rows.length) {
            throw new Error("User not found");
        };
        let {id} =  row.rows[0];
        db.query("DELETE FROM seguindo WHERE iduser = $1 AND idseguido = $2;", [req.session.userId, id]).then((row) => {
            res.send({user:req.session.userId, unfollowing: id})
        }).catch((err) => {
            res.status(404).send(`${err}`);
        });
    }).catch((err) => {
        res.status(404).send(`${err}`);
    });
});

router.get('/followers', async (req,res) => {
    if(req.session.user){
        const command = "SELECT * FROM seguindo WHERE idUser = $1";
        db.query(command, req.session.userId, []).then((row) => res.send(row.rows)).catch((err)=>{
            res.send(`${err}`);
            console.log(err);
        })
    }else{
        res.status(403).send("Not logged in"); return;
    }
})