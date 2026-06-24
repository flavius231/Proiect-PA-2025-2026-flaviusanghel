#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/entity.h"

/* =========================================================
 * entity.c
 * Implementarea ciclului de viață al entității și a funcțiilor
 * de conversie.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții de conversie
 * ---------------------------------------------------------- */

const char *entity_type_to_str(EntityType type)
{
    /* TODO: returnează șirul corespunzător fiecărei valori enum */
    if(type == PERSON)   return "PERSON";
    if(type == COMPANY)  return "COMPANY";
    if(type == LOCATION) return "LOCATION";
    if(type == EVENT)    return "EVENT";
    return "UNKNOWN";
}

EntityType str_to_entity_type(const char *str)
{
    /* TODO: compară str cu numele cunoscute și returnează enum-ul */
    if(strcmp(str, "PERSON") == 0 || strcmp(str, "person") == 0)
        return PERSON;

    if(strcmp(str, "LOCATION") == 0 || strcmp(str, "location") == 0)
        return LOCATION;

    if(strcmp(str, "COMPANY") == 0 || strcmp(str, "company") == 0)
        return COMPANY;

    if(strcmp(str, "EVENT") == 0 || strcmp(str, "event") == 0)
        return EVENT;

    return (EntityType)-1;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Entity *entity_create(const char *name, EntityType type, int id)
{
    /* TODO: alocă Entity, duplică name, atribuie câmpurile */
    Entity *entitate=malloc(sizeof(Entity));
    if(entitate == NULL){
        return NULL;
    }
    if(name!=NULL){
        entitate->name = strdup(name);
    }
    else entitate->name = NULL;
    entitate->type = type;
    entitate->id = id;
    return entitate;
}

void entity_free(Entity *e)
{
    /* TODO: eliberează name, apoi structura */
    if(e==NULL) return;
    free(e->name);
    free(e);
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void entity_print(const Entity *e)
{
    /* TODO: afișează "<id> <name> <TYPE>" */
    if(e==NULL) return;
    printf("%d %s %s\n" , e->id,e->name, entity_type_to_str(e->type));//ma gandesc daca afisez int sau vreau sa fac conversie la char
}
