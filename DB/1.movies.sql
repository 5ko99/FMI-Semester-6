SELECT * FROM MOVIE;

SELECT title from MOVIE;

select title, year
from MOVIE
where LENGTH is null;

select *
from MOVIE
where STUDIONAME like 'Fox%';

select NAME
from MOVIESTAR
where BIRTHDATE = '1977-07-07';

select distinct GENDER
from MOVIESTAR;