using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class item : MonoBehaviour {
    public enum ItemType
    {
        COLOR,      //캐릭터 색상 변결
        KEY,        //키
        CHANGE,     //먹을시 나의 색상의 블록을 해당 색으로 변경
        LASER       //레이져
    };
    public ItemType m_ItemType; 
    public Color m_color;
    private SpriteRenderer m_itemSprite;
	// Use this for initialization
	void Start () {
        m_itemSprite = GetComponent<SpriteRenderer>();
        if (m_itemSprite != null)
            m_itemSprite.color = m_color;
    }
	
	// Update is called once per frame
	void Update () {
        
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag.Equals("Player"))
        {
            cat Cat = collision.transform.GetComponent<cat>();
            if (m_ItemType.Equals(ItemType.COLOR))
            {
                Cat.GCOLOR = m_itemSprite.color;
            }
            else if (m_ItemType.Equals(ItemType.KEY))
            {
                Cat.m_isKey = true;
                Debug.Log("열쇠 획득");
            }
            else if (m_ItemType.Equals(ItemType.CHANGE))
            {
              foreach(cloud c in Cat.m_coudList) {
                    if (c.m_color.Equals(m_color))
                        c.m_SpriteRenderer.color = Cat.GCOLOR;
                    else if(c.m_color == Cat.GCOLOR)
                        c.m_SpriteRenderer.color = m_color;

                  }

            }
            else if (m_ItemType.Equals(ItemType.LASER))
            {
                if (!Cat.GCOLOR.Equals(m_color))
                {
                    SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
                }
            }
                Destroy(gameObject);
        }
    }
}
