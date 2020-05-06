const Router = require('express-promise-router')
const db = require('../db')
const router = new Router()

module.exports = router

router.get('/', async  (req,res) => {
    if(req.session.user){
        const command = "SELECT * FROM notificacao WHERE username = $1";
        db.query(command, req.session.user, []).then((row) => res.send(row.rows)).catch((err)=>{
            res.send(`${err}`);
            console.log(err);
        })
    }else{
        res.status(403).send("Not logged in"); return;
    } 
})