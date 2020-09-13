import React, { useState } from 'react';
import { View, Text, TextInput } from 'react-native';
import styles from './styles';
import PageHeader from '../../components/PageHeader';
import TeacherItem, { Teacher } from '../../components/TeacherItem';
import { ScrollView, BorderlessButton, RectButton } from 'react-native-gesture-handler';
import {Picker} from '@react-native-community/picker';
import {Feather} from '@expo/vector-icons';
import api from '../../services/api';
import AsyncStorage from '@react-native-community/async-storage';
import { useFocusEffect } from '@react-navigation/native';

function TeacherList(){

    const [teachers, setTeachers] = useState([]);

    const [favorites, setFavorites] = useState<number[]>([])

    const [isFiltersVisible, setIsFiltersVisible] = useState(false);

    const [subject, setSubject] = useState('');
    const [week_day, setWeekDay] = useState('');
    const [time, setTime] = useState('');

    function loadFavorites(){
        AsyncStorage.getItem('favorites').then(response => {
            if(response){
                const favoritedTeachers = JSON.parse(response);
                const favoritedTeachersId = favoritedTeachers.map((teacher: Teacher) => {
                    return teacher.id;
                })
                setFavorites(favoritedTeachersId);
            }
        })
    }

    useFocusEffect(()=>{
        loadFavorites();
    });

  
    function handleToggleFiltersVisible(){
        setIsFiltersVisible(!isFiltersVisible);
    }

    async function handleFiltersSubmit(){

        loadFavorites();
        const response = await api.get('classes', {
            params: {
                subject,
                week_day,
                time,
            }


        })

        setIsFiltersVisible(false);

        setTeachers(response.data);
    }

    return (
        <View style={styles.container}>
            <PageHeader title="Proffys disponiveis" headerRight={(
                <BorderlessButton onPress={handleToggleFiltersVisible}>
                    <Feather name="filter" size={20} color="#FFF"/>
                </BorderlessButton>
            )}>
                { isFiltersVisible && ( 
                <View style={styles.searchForm}>
                    <Text style={styles.label}> Materia </Text>
                    <TextInput
                        placeholderTextColor='#c1bccc'
                        style={styles.input}
                        value={subject}
                        onChangeText={text => setSubject(text)}
                        placeholder="Qual a materia?"
                    />

                    <View style={styles.inputGroup}>
                        <View style={styles.inputBlock}>
                            <Text style={styles.label}> Dia da semana </Text>
                            <TextInput
                                placeholderTextColor='#c1bccc'
                                style={styles.input}
                                value={week_day}
                                onChangeText={text => setWeekDay(text)}
                                placeholder="Qual o dia?"
                            />
                        </View>

                        <View style={styles.inputBlock}>
                            <Text style={styles.label}> Horario </Text>
                            <TextInput
                                placeholderTextColor='#c1bccc'
                                style={styles.input}
                                value={time}
                                onChangeText={text => setTime(text)}
                                placeholder="Qual horario?"
                            />
                        </View>

                    </View>

                    <RectButton onPress={handleFiltersSubmit} style={styles.submitButton}>
                        <Text style={styles.submitButtonText}>Filtrar</Text>

                    </RectButton>

                </View>
                )}
            </PageHeader>

            <ScrollView style={styles.teacherList} contentContainerStyle={{
                paddingHorizontal: 16,
                paddingBottom: 16
            }}>

                {teachers.map((teacher: Teacher) => {
                    return(
                        <TeacherItem
                         key={teacher.id}
                         teacher={teacher}
                         favorited={favorites.includes(teacher.id)}
                         />)
                })}
                
            </ScrollView>
        </View>
    )
}

export default TeacherList;