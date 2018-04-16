using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class endpoint : MonoBehaviour {
    private GameData date = new GameData();
    private int m_SceneNumber;
	// Use this for initialization
	void Start () {
        m_SceneNumber = SceneManager.GetActiveScene().buildIndex;
        date.SetScene(m_SceneNumber);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.transform.tag.Equals("Player"))
        {
            GetComponent<BoxCollider2D>().enabled = false;
            cat Cat = collision.transform.GetComponent<cat>();
            if (Cat.m_isKey == true)
            {
                date.SetScene(date.GetcurrScene() + 1);
                string Scene = "Level" + date.GetcurrScene();
                if (date.GetcurrScene() == 11)
                    SceneManager.LoadScene("End_Scene");
                else
                    SceneManager.LoadScene(Scene);

            }
            
        }
    }
}
