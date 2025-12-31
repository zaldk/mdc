#define MATERIAL_SCHEME_DARK \
    X(Primary,                 Primary,   80) \
    X(OnPrimary,               Primary,   20) \
    X(PrimaryContainer,        Primary,   30) \
    X(OnPrimaryContainer,      Primary,   90) \
    X(Secondary,               Secondary, 80) \
    X(OnSecondary,             Secondary, 20) \
    X(SecondaryContainer,      Secondary, 30) \
    X(OnSecondaryContainer,    Secondary, 90) \
    X(Tertiary,                Tertiary,  80) \
    X(OnTertiary,              Tertiary,  20) \
    X(TertiaryContainer,       Tertiary,  30) \
    X(OnTertiaryContainer,     Tertiary,  90) \
    X(PrimaryFixed,            Primary,   90) \
    X(OnPrimaryFixed,          Primary,   10) \
    X(PrimaryFixedDim,         Primary,   80) \
    X(OnPrimaryFixedVariant,   Primary,   30) \
    X(InversePrimary,          Primary,   40) \
    X(SecondaryFixed,          Secondary, 90) \
    X(OnSecondaryFixed,        Secondary, 10) \
    X(SecondaryFixedDim,       Secondary, 80) \
    X(OnSecondaryFixedVariant, Secondary, 30) \
    X(TertiaryFixed,           Tertiary,  90) \
    X(OnTertiaryFixed,         Tertiary,  10) \
    X(TertiaryFixedDim,        Tertiary,  80) \
    X(OnTertiaryFixedVariant,  Tertiary,  30) \
    X(Error,                   Error,     80) \
    X(OnError,                 Error,     20) \
    X(ErrorContainer,          Error,     30) \
    X(OnErrorContainer,        Error,     90) \
    X(Surface,                 Neutral,    6) \
    X(OnSurface,               Neutral,   90) \
    X(SurfaceVariant,          Neutral,   30) \
    X(OnSurfaceVariant,        Neutral,   80) \
    X(SurfaceContainerHighest, Neutral,   22) \
    X(SurfaceContainerHigh,    Neutral,   17) \
    X(SurfaceContainer,        Neutral,   12) \
    X(SurfaceContainerLow,     Neutral,   10) \
    X(SurfaceContainerLowest,  Neutral,    6) \
    X(InverseSurface,          Neutral,   90) \
    X(InverseOnSurface,        Neutral,   20) \
    X(Outline,                 Neutral,   60) \
    X(OutlineVariant,          Neutral,   30) \
    X(SurfaceBright,           Neutral,   24) \
    X(SurfaceDim,              Neutral,    6) \
    X(Background,              Neutral,    6) \
    X(OnBackground,            Neutral,   90)

#define MATERIAL_SCHEME_LIGHT \
    X(Primary,                 Primary,   40) \
    X(OnPrimary,               Primary,  100) \
    X(PrimaryContainer,        Primary,   90) \
    X(OnPrimaryContainer,      Primary,   30) \
    X(Secondary,               Secondary, 40) \
    X(OnSecondary,             Secondary,100) \
    X(SecondaryContainer,      Secondary, 90) \
    X(OnSecondaryContainer,    Secondary, 30) \
    X(Tertiary,                Tertiary,  40) \
    X(OnTertiary,              Tertiary, 100) \
    X(TertiaryContainer,       Tertiary,  90) \
    X(OnTertiaryContainer,     Tertiary,  30) \
    X(PrimaryFixed,            Primary,   90) \
    X(OnPrimaryFixed,          Primary,   10) \
    X(PrimaryFixedDim,         Primary,   80) \
    X(OnPrimaryFixedVariant,   Primary,   30) \
    X(InversePrimary,          Primary,   80) \
    X(SecondaryFixed,          Secondary, 90) \
    X(OnSecondaryFixed,        Secondary, 10) \
    X(SecondaryFixedDim,       Secondary, 80) \
    X(OnSecondaryFixedVariant, Secondary, 30) \
    X(TertiaryFixed,           Tertiary,  90) \
    X(OnTertiaryFixed,         Tertiary,  10) \
    X(TertiaryFixedDim,        Tertiary,  80) \
    X(OnTertiaryFixedVariant,  Tertiary,  30) \
    X(Error,                   Error,     40) \
    X(OnError,                 Error,    100) \
    X(ErrorContainer,          Error,     90) \
    X(OnErrorContainer,        Error,     30) \
    X(Surface,                 Neutral,   98) \
    X(OnSurface,               Neutral,   10) \
    X(SurfaceVariant,          Neutral,   90) \
    X(OnSurfaceVariant,        Neutral,   30) \
    X(SurfaceContainerHighest, Neutral,   98) \
    X(SurfaceContainerHigh,    Neutral,   96) \
    X(SurfaceContainer,        Neutral,   94) \
    X(SurfaceContainerLow,     Neutral,   92) \
    X(SurfaceContainerLowest,  Neutral,   90) \
    X(InverseSurface,          Neutral,   20) \
    X(InverseOnSurface,        Neutral,   95) \
    X(Outline,                 Neutral,   50) \
    X(OutlineVariant,          Neutral,   80) \
    X(SurfaceBright,           Neutral,   98) \
    X(SurfaceDim,              Neutral,   87) \
    X(Background,              Neutral,   98) \
    X(OnBackground,            Neutral,   10)

/* CHANGES:
I changed the light theme's surface containers to match:
    lowest  = darkest
    highest = brightest
        SurfaceContainerHighest  90 <- 98
        SurfaceContainerHigh     92 <- 96
        SurfaceContainer         94 <- 94
        SurfaceContainerLow      96 <- 92
        SurfaceContainerLowest  100 <- 90

And i changed:
    Dark  Lowest  == Dark  Surface
    Light Highest == Light Surface
        SurfaceContainerHighest 100 <- 98
        SurfaceContainerLowest 4 <- 6
*/
