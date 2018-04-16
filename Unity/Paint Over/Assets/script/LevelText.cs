using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LevelText : MonoBehaviour {
    private int m_SceneNumber;
    public Text text;
    // Use this for initialization
    void Start () {
        m_SceneNumber = SceneManager.GetActiveScene().buildIndex;
    }
	
	// Update is called once per frame
	void Update () {
        text.text = "Level " + m_SceneNumber;
	}
}
