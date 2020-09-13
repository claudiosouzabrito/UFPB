import {StyleSheet} from "react-native";

const styles = StyleSheet.create({
    container:{
        padding: 40,
        backgroundColor: '#8257e5',
    },

    topBar:{
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'space-between',
    },

    header:{
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'center',
    },

    title:{
        fontFamily:'Archivo_700Bold',
        color: '#FFF',
        fontSize: 20,
        lineHeight: 32,
        maxWidth: 160,
        marginVertical: 15,
        marginLeft: -100
    }
});

export default styles;