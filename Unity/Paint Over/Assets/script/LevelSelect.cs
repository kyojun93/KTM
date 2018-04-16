using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LevelSelect : MonoBehaviour {
    public GameObject Menu;
    private void Start()
    {

    }
    public void Levelclick(int select)
    {
        string Scene = "Level" + select;
        SceneManager.LoadScene(Scene);
    }
    public void GameStartClick(bool b)
    {
        Menu.SetActive(b);
    }
    public void ExitClick()
    {
        Application.Quit();
    }

}
