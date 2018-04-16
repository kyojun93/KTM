using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameData{
    public static int currStage = 1;
    public static int StageEnd = 11;
    public enum eDataEnum
    {
        STAGE_END = 11,
    }
    public int[] GameStaege = new int[11] { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    // public static eDataEnum stageEnd = eDataEnum.STAGE_END;
    //public static const int EndStage = 12;
    // Use this for initialization
    
    public int GetcurrScene()
    {
        return currStage;

    }
    public void SetScene(int scene)
    {
        currStage = scene;
    }
    public void setStage(int index, int i)
    {
        GameStaege[index] = i;
    }
    public int getStage(int index)
    {
        return GameStaege[index];
    }
}
