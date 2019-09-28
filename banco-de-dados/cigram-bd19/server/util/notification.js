const db = require('../db')


module.exports = {
    notifyUser : async function(idNot, type, userDoing, userReceiving){
        const time = new Date();
        const getTopic = "INSERT INTO notificacao (idnot, tipo, sujeito, objeto, time) VALUES ($1, $2, $3, $4, $5);";
        const notificacao = await db.query(getTopic, [idNot, type, userDoing, userReceiving, time]);
        return notificacao;
    },

    notificacaoPost : async function(idNot, idPost){
        const getTopic = "INSERT INTO notificacao_post (idnot, idPost) VALUES ($1, $2);";
        return await db.query(getTopic, [idNot, idpost]);
    },

    notificacaoComentario : async function(idNot, idComent){
        const getTopic = "INSERT INTO notificacao_comentario (idnot, idComent) VALUES ($1, $2);";
        return await db.query(getTopic, [idNot, idComent]);
    }
}