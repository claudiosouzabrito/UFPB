const Router = require('express-promise-router')
const db = require('../db')
const uuidv1 = require("uuid/v1")

const router = new Router()

module.exports = router

/******************************************
*
*   Getting all Post with x topics
*   Method: POST
*   Payload Type: json 
*   Payload Content: hashtag
*
*******************************************/

router.post('/', async (req, res)=>{
    if(req.session.user){
        const query = "SELECT post.idPost, post.idUser, post.idFoto, post.texto, post.datestamp FROM topico_post INNER JOIN post ON topico_post.idPost = post.idPost INNER JOIN usuario ON post.idUser = usuario.id WHERE usuario.privacidade = False AND topico_post.hashtag = $1 ORDER BY datestamp DESC;";
        try {
            const topicoPosts = await db.query(query, [ req.body.hashtag ]);
            res.send(topicoPosts.rows);        
        } catch (error) {
            res.status(404).send(error);
        }
    }else{
        res.send("Not logged in");
    }
})