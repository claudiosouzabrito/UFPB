import React, { useState, useEffect } from 'react';
import {View, Image, Text} from 'react-native';
import {useNavigation, NavigationHelpersContext} from '@react-navigation/native';
import styles from './styles';
import landingImg from '../../assets/images/landing.png';
import studyIcon from '../../assets/images/icons/study.png';
import giveClassesIcon from '../../assets/images/icons/give-classes.png';
import heartIcon from '../../assets/images/icons/heart.png';
import {RectButton} from 'react-native-gesture-handler'
import api from '../../services/api';
function Landing(){

    const {navigate} = useNavigation();

    const [totalConections, setTotalConections] = useState(0);

    useEffect(() => {
        api.get('connections').then(response => {
            const {total} = response.data;

            setTotalConections(total);
        })
    }, [])


    function handleNavigateToGiveCLassesPage(){
        navigate('GiveClasses');
    }

    function handleNavigateToStudyPage(){
        navigate('Study');
    }

    return (
        <View style={styles.container}>
            <Image source={landingImg} style={styles.banner} />
            <Text style={styles.title}>
                Seja bem-vindo, {'\n'}
                <Text style={styles.titleBold}>0 que deseja fazer?</Text>
            </Text>

            <View style={styles.buttonsContainer}>
                <RectButton 
                    onPress={handleNavigateToStudyPage} 
                    style={[styles.button, styles.buttonPrimary]}
                >

                    <Image source={studyIcon}/>

                    <Text style={styles.buttonText}> Estudar </Text>
                </RectButton>

                <RectButton onPress={handleNavigateToGiveCLassesPage} style={[styles.button, styles.buttonSecondary]}>
                    <Image source={giveClassesIcon}/>

                    <Text style={styles.buttonText}> Dar aulas </Text>
                </RectButton>

            </View>

            <Text style={styles.totalConnections}>
                Total de {totalConections} conexoes ja realizadas {''}
                <Image source={heartIcon}/>
            </Text>

        </View>
    )
}

export default Landing;