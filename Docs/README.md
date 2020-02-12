# Town Generator

Michael Burrowes' Town Generation app for DMs to make towns with. This README will contain preliminary docs.

## Sectors

Sectors are different parts of a town. Each type of sector has a `weight` which controls what percent of the town's area (or population?) is a sector of that type. Sectors also have an `urbanizationScale` which controls the (wealth? modernity? industrial-ness?) of that sector type.

A sector is specified in the `Sectors.dma` file in the format 

```CSV
<sectorName>,<sectorWeight>,<sectorUrbanizationScale>
```

## Races

Races have a `name` and a `vector` of scales for each `Sector` type in the city. This controls the population density of that race in that `Sector` type.

A race is specified in the `Races.dma` file in the format

```CSV
<raceName><vector<double> sectorScales>
```
Example:
```CSV
Human,0.3,0.0,0.5,0.0,0.3,0.3,0.1,0.2,0.1,0.7,0.2,0.2,0.0,0.9,0.4,0.5
```

## Professions

Each resident of the town has an associated `Profession`, specified by a `name`, a `Sector` in which that `Profession` is (_most likely to be?_) found, a weight of that `Profession` which controls the amount of people with that profession, and an `urbanizationScale` which does idk what.

Professions are specified like so:

```CSV
<professionName>,<sectorVector>
```

For example,

```
Falconer,1,0.02,,,
```