namespace HD {
    extern int firstStart;

    void ResizeWindow_Interception();
    void ResizeRenderResolution_Interception();
    void ResizeForgroundRenderWidth_Interception();
    int Replace640_ResizeGameLogicResolution_Interception();
    void Replace640_ResizeD2DWindow_Interception();
    void Replace640_ResizeD2D_Interception1();
    void Replace640_ResizeGlideRenderResolution_Interception();
    void Replace640_ResizeGlideWindow_Interception();
    int SetupGlideRenderResolution();

    void RepositionPanels();

    int GetResolutionMode_Patch();
}
